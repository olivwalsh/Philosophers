/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:40:39 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/17 11:10:32 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_sim *data)
{
	t_philo	*philo;
	t_philo	*ptr;
	int		i;

	ptr = NULL;
	i = 0;
	if (data->head)
	{
		philo = data->head;
		while (i < data->number && philo)
		{
			ptr = philo;
			philo = philo->next;
			pthread_mutex_destroy(&ptr->fork);
			if (ptr)
				free(ptr);
			i++;
		}
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death);
}

int	exitsim(t_sim *data)
{
	t_philo	*current;
	int		i;

	current = data->head;
	i = 0;
	while (i < data->number && current)
	{
		if (pthread_join(current->id, NULL))
			return (EXIT_FAILURE);
		current = current->next;
		i++;
	}
	return (EXIT_SUCCESS);
}
