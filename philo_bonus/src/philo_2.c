/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:04:46 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/17 16:56:06 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	if (check_sim_end(philo))
		return (1);
	if (!check_meals_count(philo) && \
		timediff(philo->sim->t0, timestamp()) > philo->sim->time_to_die)
	{
		printlog(philo, "died");
		sem_wait(philo->sim->death);
		philo->sim->sim_end = 1;
		sem_wait(philo->sim->death);
		return (1);
	}
	if (check_meals_count(philo) && \
		(last_time_eaten(philo) > philo->sim->time_to_die))
	{
		printlog(philo, "died");
		sem_wait(philo->sim->death);
		philo->sim->sim_end = 1;
		sem_wait(philo->sim->death);
		return (1);
	}
	return (0);
}

int	check_sim_end(t_philo *philo)
{
	int	end;

	sem_wait(philo->sim->death);
	end = philo->sim->sim_end;
	sem_post(philo->sim->death);
	return (end);
}

int	check_meals_count(t_philo *philo)
{
	int	meals;

	sem_wait(philo->sim->death);
	meals = philo->meals;
	sem_post(philo->sim->death);
	return (meals);
}

long long	last_time_eaten(t_philo *philo)
{
	long long	last_time_eaten_ms;

	sem_wait(philo->sim->death);
	last_time_eaten_ms = timediff(philo->last_meal, timestamp());
	sem_post(philo->sim->death);
	return (last_time_eaten_ms);
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
		usleep(100);
		if (is_dead(current))
			return (NULL);
		current = current->next;
	}
	return (NULL);
}
