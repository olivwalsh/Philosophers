/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:06:57 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/17 11:10:36 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pickup_forks(t_philo *philo)
{
	if (!philo->prev)
	{
		pthread_mutex_lock(&philo->fork);
		printlog(philo, "has taken a fork");
		usleep((philo->sim->time_to_die) * 1000);
		printlog(philo, "died");
		pthread_mutex_unlock(&philo->fork);
		return (0);
	}
	if (philo->nb % 2)
	{
		pthread_mutex_lock(&philo->fork);
		printlog(philo, "has taken a fork");
		pthread_mutex_lock(&philo->prev->fork);
		printlog(philo, "has taken a fork");
	}
	else
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
	if (!philo->is_full && pickup_forks(philo))
	{
		pthread_mutex_lock(&philo->sim->death);
		philo->last_meal = timestamp();
		philo->meals++;
		pthread_mutex_unlock(&philo->sim->death);
		printlog(philo, "is eating");
		usleep(philo->sim->time_to_eat * 1000);
		putdown_forks(philo);
		if (philo->sim->meals_per_philo && \
			check_meals_count(philo) == philo->sim->meals_per_philo)
		{
			pthread_mutex_lock(&philo->sim->death);
			philo->is_full = 1;
			pthread_mutex_unlock(&philo->sim->death);
		}
	}
}

void	*philo_life(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	while (!check_sim_end(philo) && !philo->is_full)
	{
		eat(philo);
		if (!philo->prev)
			return (NULL);
		printlog(philo, "is sleeping");
		usleep(philo->sim->time_to_sleep * 1000);
		printlog(philo, "is thinking");
		usleep(300);
	}
	return (NULL);
}

int	execute(t_sim *data)
{
	t_philo		*current;
	pthread_t	monitor;
	int			i;

	gettimeofday(&data->t0, NULL);
	if (pthread_mutex_init(&data->print, NULL))
		return (EXIT_FAILURE);
	current = data->head;
	i = 0;
	if (pthread_create(&monitor, NULL, &check_end, data))
		return (EXIT_FAILURE);
	if (pthread_detach(monitor))
		return (EXIT_FAILURE);
	while (i < data->number && current)
	{
		if (pthread_create(&current->id, NULL, &philo_life, current))
			return (EXIT_FAILURE);
		current = current->next;
		i++;
	}
	return (exitsim(data));
}
