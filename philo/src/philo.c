/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:06:57 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/16 14:10:22 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pickup_forks(t_philo *philo)
{
	if (!philo->prev)
	{
		printlog(philo, "has no prev philo");
		usleep((philo->sim->time_to_die  + 15) * 1000);
		return (0);
	}
	if (philo->nb % 2) // odd philos pick first its own fork, then prev fork
	{
		pthread_mutex_lock(&philo->fork);
		printlog(philo, "has taken a fork");
		pthread_mutex_lock(&philo->prev->fork);
		printlog(philo, "has taken a fork");
	}
	else // even philos pick first prev fork, then its own
	{
		pthread_mutex_lock(&philo->prev->fork);
		printlog(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork);
		printlog(philo, "has taken a fork");
	}
	return (1);
}

void	putdown_forks(t_philo *philo)
{
	if (philo->nb % 2)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->prev->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->prev->fork);
		pthread_mutex_unlock(&philo->fork);
	}
}

void	eat(t_philo	*philo)
{
	pthread_mutex_lock(&philo->last_m);
	if (!philo->is_full && pickup_forks(philo))
	{
		philo->last_meal = timestamp();
		printlog(philo, "is eating");
		philo->meals++;
		usleep(philo->sim->time_to_eat * 1000);
		putdown_forks(philo);
		if (philo->sim->meals_per_philo && philo->meals == philo->sim->meals_per_philo)
			philo->is_full = 1;
	}
	pthread_mutex_unlock(&philo->last_m);
}

void	*check_end(void * ptr)
{
	t_philo	*current;

	current = (t_philo *)ptr;
	usleep(10000);
	while (!current->sim->sim_end)
	{
		usleep(100);
		if (current->is_full)
			return (NULL);
		if (is_dead(current))
			return (NULL);
		current = current->next;
	}
	return (NULL);
}

void	*philo_life(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	while (!philo->sim->sim_end && !philo->is_full)
	{
		eat(philo);
		if (!philo->prev)
			return (NULL);
		printlog(philo, "is sleeping");
		usleep(philo->sim->time_to_sleep * 1000);
		printlog(philo, "is thinking");
	}
	return (NULL);
}

int	execute(t_sim *data)
{
	t_philo	*current;
	pthread_t	monitor;
	int		i;

	gettimeofday(&data->t0, NULL);
	if (pthread_mutex_init(&data->print, NULL))
		return (EXIT_FAILURE);
	current = data->head;
	i = 0;
	if (pthread_create(&monitor, NULL, &check_end, current))
		return (EXIT_FAILURE);
	if (pthread_detach(monitor))
		return (EXIT_FAILURE);
	while (i < data->number)
	{
		if (pthread_mutex_init(&current->fork, NULL))
			return (EXIT_FAILURE);
		if (pthread_create(&current->id, NULL, &philo_life, current))
			return (EXIT_FAILURE);
		current = current->next;
		i++;
	}
	
	return (exitsim(data));
}

int exitsim(t_sim *data)
{
	t_philo	*current;
	int		i;

	current = data->head;
	i = 0;
	while (i < data->number)
	{
		if (pthread_join(current->id, NULL))
			return (EXIT_FAILURE);
		if (pthread_mutex_destroy(&current->fork))
			return (EXIT_FAILURE);
		current = current->next;
		i++;
	}
	if (pthread_mutex_destroy(&data->print))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
