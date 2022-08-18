/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:04:46 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/18 11:06:10 by owalsh           ###   ########.fr       */
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
		sem_wait(philo->sim->death);
		philo->sim->sim_end = 1;
		exit (1);
	}
	if (check_meals_count(philo) && \
		(last_time_eaten(philo) > philo->sim->time_to_die))
	{
		printlog(philo, "died");
		sem_wait(philo->sim->death);
		philo->sim->sim_end = 1;
		exit (1);
	}
	return (0);
}

int	check_is_full(t_philo *philo)
{
	int	end;

	sem_wait(philo->sim->death);
	end = philo->is_full;
	sem_post(philo->sim->death);
	return (end);
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

void	*check_end(void *ptr)
{
	t_philo	*current;

	current = (t_philo *)ptr;
	usleep(10000);
	if (current->sim->number == 1)
		return (NULL);
	while (1)
	{
		usleep(100);
		if (is_dead(current))
			return (NULL);
	}
	return (NULL);
}
