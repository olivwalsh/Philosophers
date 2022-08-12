/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:04:46 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/12 12:17:18 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	if (philo->meals && \
		(timediff(philo->sim->t0, philo->last_meal)) > philo->sim->time_to_die)
	{
		printlog(philo, "died");
		return (1);
	}
	else if (timediff(philo->sim->t0, timestamp()) > philo->sim->time_to_die)
	{
		printlog(philo, "died");
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
