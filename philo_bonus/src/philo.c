/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:06:57 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/18 09:19:24 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pickup_forks(t_philo *philo)
{
	if (!philo->prev)
	{
		sem_wait(philo->sim->forks);
		printlog(philo, "has taken a fork");
		usleep((philo->sim->time_to_die) * 1000);
		printlog(philo, "died");
		sem_post(philo->sim->forks);
		return (0);
	}
	sem_wait(philo->sim->forks);
	printlog(philo, "has taken a fork");
	sem_wait(philo->sim->forks);
	printlog(philo, "has taken a fork");
	return (1);
}

void	putdown_forks(t_philo *philo)
{
	sem_post(philo->sim->forks);
	sem_post(philo->sim->forks);
}

void	eat(t_philo	*philo)
{
	if (!philo->is_full && pickup_forks(philo))
	{
		sem_wait(philo->sim->death);
		philo->last_meal = timestamp();
		philo->meals++;
		sem_post(philo->sim->death);
		printlog(philo, "is eating");
		usleep(philo->sim->time_to_eat * 1000);
		putdown_forks(philo);
		if (philo->sim->meals_per_philo && \
			check_meals_count(philo) == philo->sim->meals_per_philo)
		{
			sem_wait(philo->sim->death);
			philo->is_full = 1;
			sem_post(philo->sim->death);
		}
	}
}

int	philo_life(t_philo *philo)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &check_end, philo))
		return (1);
	if (pthread_detach(monitor))
		return (1);
	while (!check_sim_end(philo) && !philo->is_full)
	{
		eat(philo);
		if (!philo->prev)
			return (1);
		printlog(philo, "is sleeping");
		usleep(philo->sim->time_to_sleep * 1000);
		printlog(philo, "is thinking");
	}
	return (0);
}

int	execute(t_sim *data)
{
	t_philo		*current;
	int			i;

	gettimeofday(&data->t0, NULL);
	current = data->head;
	i = 0;
	while (i < data->number && current)
	{
		current->pid = fork();
		if (current->pid < 0)
			return (-1);
		else if (current->pid == 0)
		{
			if (philo_life(current))
				exit(1);
			exit(0);
		}
		current = current->next;
		i++;
	}
	return (exitsim(data));
}
