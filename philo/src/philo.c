/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:06:57 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/12 16:33:57 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickup_forks(t_philo *philo)
{
	if (!philo->prev)
		return ;
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
}

void	putdown_forks(t_philo *philo)
{
	if (!philo->prev)
		return ;
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
	pickup_forks(philo);
	printlog(philo, "is eating");
	philo->last_meal = timestamp();
	usleep(philo->sim->time_to_eat * 1000);
	putdown_forks(philo);
	philo->meals++;
	if (philo->sim->meals_per_philo && philo->meals == philo->sim->meals_per_philo)
		philo->is_full = 1;
}

void	*check_end(void * ptr)
{
	t_philo	*current;

	current = (t_philo *)ptr;
	usleep(1000);
	while (!current->sim->sim_end)
	{
		(usleep(100));
		if (is_dead(current))
			return (NULL);
	}
	return (NULL);
}

void	*philo_life(void *ptr)
{
	t_philo		*philo;
	pthread_t	monitor;

	philo = (t_philo *)ptr;
	if (pthread_create(&monitor, NULL, &check_end, philo))
		return (NULL);
	pthread_detach(monitor);
	while (!dead_philo(philo->sim) && philo_hungry(philo->sim))
	{
		eat(philo);
		printlog(philo, "is sleeping");
		usleep(philo->sim->time_to_sleep * 1000);
		printlog(philo, "is thinking");
	}
	return (NULL);
}

int	execute(t_sim *data)
{
	t_philo	*current;
	
	int		i;

	gettimeofday(&data->t0, NULL);
	if (pthread_mutex_init(&data->print, NULL))
		return (EXIT_FAILURE);
	current = data->head;
	i = 0;
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
