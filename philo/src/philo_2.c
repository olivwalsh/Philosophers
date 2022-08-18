/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:04:46 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/18 12:01:33 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	if (check_is_full(philo))
		return (0);
	if (check_sim_end(philo))
		return (1);
	if (!check_meals_count(philo) && \
		timediff(philo->sim->t0, timestamp()) > philo->sim->time_to_die)
	{
		printlog(philo, "died");
		pthread_mutex_lock(&philo->sim->death);
		philo->sim->sim_end = 1;
		pthread_mutex_unlock(&philo->sim->death);
		return (1);
	}
	if (check_meals_count(philo) && \
		(last_time_eaten(philo) > philo->sim->time_to_die))
	{
		printlog(philo, "died");
		pthread_mutex_lock(&philo->sim->death);
		philo->sim->sim_end = 1;
		pthread_mutex_unlock(&philo->sim->death);
		return (1);
	}
	return (0);
}

int	check_sim_end(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(&philo->sim->death);
	end = philo->sim->sim_end;
	pthread_mutex_unlock(&philo->sim->death);
	if (end)
		return (end);
	else
		return (check_is_full(philo));
}

int	check_is_full(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(&philo->sim->death);
	end = philo->is_full;
	pthread_mutex_unlock(&philo->sim->death);
	return (end);
}

int	check_meals_count(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->sim->death);
	meals = philo->meals;
	pthread_mutex_unlock(&philo->sim->death);
	return (meals);
}

void	*check_end(void *ptr)
{
	t_sim	*data;
	t_philo	*current;

	data = (t_sim *)ptr;
	usleep(10000);
	if (data->number == 1)
		return (NULL);
	current = data->head;
	while (current && !check_sim_end(current))
	{
		usleep(200);
		if (is_dead(current))
			return (NULL);
		current = current->next;
	}
	return (NULL);
}
