/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:04:46 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/10 12:37:03 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	if (philo->last_meal && \
		(get_time(philo->sim) - philo->last_meal) > philo->sim->time_to_die)
	{
		pthread_mutex_lock(&philo->sim->print);
		printf("%ld: %d died\n", get_time(philo->sim), philo->nb);
		pthread_mutex_unlock(&philo->sim->print);
		return (1);
	}
	else if (get_time(philo->sim) > philo->sim->time_to_die)
	{
		pthread_mutex_lock(&philo->sim->print);
		printf("%ld: %d died\n", get_time(philo->sim), philo->nb);
		pthread_mutex_unlock(&philo->sim->print);
		return (1);
	}
	return (0);
}

int	dead_philo(t_sim *data)
{
	t_philo	*current;

	current = data->head;
	while (current)
	{
		if (is_dead(current))
			return (1);
		current = current->next;
	}
	return (0);
}

int	philo_hungry(t_sim *data)
{
	t_philo	*current;

	if (data->meals_per_philo)
	{
		current = data->head;
		while (current)
		{
			if (current->meals < data->meals_per_philo)
				return (1);
			current = current->next;
		}
		return (0);
	}
	else
		return (1);
}
