/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:26:39 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/05 16:27:48 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*i_s;
	size_t	i;

	i_s = s;
	i = 0;
	while (s && i < n)
	{
		i_s[i] = c;
		i++;
	}
	return (s);
}

t_philo	*get_last_philo(t_philo *first)
{
	t_philo	*current;

	if (!first)
		return (NULL);
	if (!first->next)
		return (first);
	current = first;
	while (current->next != first)
		current = current->next;
	return (current);
}

void	display_simulation(t_sim *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	printf("------------ SIM DISPLAY ------------\n");
	printf("sim->number_of_philosophers = %d\n", data->number);
	printf("sim->time_to_die = %ld ms\n", data->time_to_die);
	printf("sim->time_to_eat = %ld ms\n", data->time_to_eat);
	printf("sim->time_to_sleep = %ld ms\n", data->time_to_sleep);
	printf("sim->meals_per_philo = %d\n", data->meals_per_philo);
	printf("---- list of philos ----\n");
	philo = data->philo;
	while (i < data->number)
	{
		printf("philo n.%d, thread_id: %ld\t\tprev = %p\t curr = %p\t next = %p\n", philo->nb, philo->id, philo->prev, philo, philo->next);
		philo = philo->next;
		i++;
	}
	printf("--------------------------------------\n");
}
