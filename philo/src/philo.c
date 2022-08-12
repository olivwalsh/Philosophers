/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:06:57 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/12 14:40:02 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	printlog(philo, "has taken a fork");
	if (philo->nb % 2) // odd philos pick left fork
		pthread_mutex_lock(&philo->next->fork);
	else // even philos pick right fork
		pthread_mutex_lock(&philo->prev->fork);
	printlog(philo, "has taken a fork");
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	if (philo->nb % 2)
		pthread_mutex_unlock(&philo->next->fork);
	else
		pthread_mutex_unlock(&philo->prev->fork);
}

void	eat(t_philo	*philo)
{
	pickup_forks(philo);
	printlog(philo, "is eating");
	philo->last_meal = timestamp();
	philo->meals++;
	usleep(philo->sim->time_to_eat * 1000);
	putdown_forks(philo);
}

void	*philo_life(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (!dead_philo(philo->sim) && philo_hungry(philo->sim))
	{
		eat(philo);
		printlog(philo, "is sleeping");
		usleep(philo->sim->time_to_sleep * 1000);
		printlog(philo, "is thinking");
	}
	return (NULL);
}

void	*check_end(void * ptr)
{
	t_sim	*data;
	t_philo	*current;

	data = (t_sim *)ptr;
	current = data->head;
	while (!data->sim_end)
	{
		(usleep(100));
		if (is_dead(current))
			return (NULL);
		current = current->next;
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
	while (i < data->number)
	{
		if (pthread_create(&current->id, NULL, &philo_life, current))
			return (EXIT_FAILURE);
		current = current->next;
		i++;
	}
	if (pthread_create(&monitor, NULL, &check_end, data))
		return (EXIT_FAILURE);
	pthread_detach(monitor);
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
		current = current->next;
		i++;
	}
	if (pthread_mutex_destroy(&data->print))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
