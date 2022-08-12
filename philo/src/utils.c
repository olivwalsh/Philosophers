/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:26:39 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/12 12:10:23 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printlog(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->sim->print);
	printf("%lld: ", timediff(philo->sim->t0, timestamp()));
	printf("Philosopher n.%d ", philo->nb);
	printf("%s\n", str);
	pthread_mutex_unlock(&philo->sim->print);
}

t_philo	*get_last_philo(t_philo *first)
{
	t_philo	*current;

	if (!first)
		return (NULL);
	if (!first->next)
		return (first);
	current = first;
	while (current->next)
		current = current->next;
	return (current);
}

struct	timeval	timestamp()
{
	struct timeval	now;
	gettimeofday(&now, NULL);
	return (now);
}

long long	timediff(struct timeval t0, struct timeval now)
{
	long long	now_ms;
	long long	t0_ms;

	now_ms = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	t0_ms = (t0.tv_sec * 1000) + (t0.tv_usec / 1000);
	return (now_ms - t0_ms);
}

void	display_simulation(t_sim *data)
{
	int		i;
	t_philo	*philo;
	long	pid;

	i = 0;
	printf("------------ SIM DISPLAY ------------\n");
	printf("sim->number_of_philosophers = %d\n", data->number);
	printf("sim->time_to_die = %ld ms\n", data->time_to_die);
	printf("sim->time_to_eat = %ld ms\n", data->time_to_eat);
	printf("sim->time_to_sleep = %ld ms\n", data->time_to_sleep);
	printf("sim->meals_per_philo = %d\n", data->meals_per_philo);
	printf("---- list of philos ----\n");
	philo = data->head;
	while (i < data->number)
	{
		pid = (long)philo->id;
		if (i == 0)
			printf("philo n.%d, thread_id: %ld\t\tprev = %p\t\t curr = %p\t next = %p\n", philo->nb, pid, philo->prev, philo, philo->next);
		else
			printf("philo n.%d, thread_id: %ld\t\tprev = %p\t curr = %p\t next = %p\n", philo->nb, pid, philo->prev, philo, philo->next);
		philo = philo->next;
		i++;
	}
	printf("--------------------------------------\n");
}
