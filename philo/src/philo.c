/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:06:57 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/12 12:16:01 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo	*philo)
{
	pthread_mutex_lock(&philo->fork);
	printlog(philo, "has taken a fork");
	if (philo->next)
		pthread_mutex_lock(&philo->next->fork);
	else
		pthread_mutex_lock(&philo->sim->head->fork);
	printlog(philo, "has taken a fork");
	printlog(philo, "is eating");
	philo->last_meal = timestamp();
	philo->meals++;
	usleep(philo->sim->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	if (philo->next)
		pthread_mutex_unlock(&philo->next->fork);
	else
		pthread_mutex_unlock(&philo->sim->head->fork);
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

int	execute(t_sim *data)
{
	t_philo	*current;

	gettimeofday(&data->t0, NULL);
	if (pthread_mutex_init(&data->print, NULL))
		return (EXIT_FAILURE);
	current = data->head;
	while (current)
	{
		if (pthread_create(&current->id, NULL, &philo_life, current))
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (exitsim(data));
}

int exitsim(t_sim *data)
{
	t_philo	*current;

	current = data->head;
	while (current)
	{
		if (pthread_join(current->id, NULL))
			return (EXIT_FAILURE);
		current = current->next;
	}
	if (pthread_mutex_destroy(&data->print))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
