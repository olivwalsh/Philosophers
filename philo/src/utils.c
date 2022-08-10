/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:26:39 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/10 13:13:14 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long	get_time(t_sim *data)
{ 
	struct timeval	now;
	long			time;

	gettimeofday(&now, NULL);
	time = ((now.tv_sec * 1000) + (now.tv_usec / 1000)) \
	- ((data->t0.tv_sec * 1000) + (data->t0.tv_usec / 1000));
	return (time);
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
