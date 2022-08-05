/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:28:17 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/05 16:26:43 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo(int id)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->nb = id;
	pthread_mutex_init(&new->fork, NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	lstadd_philo(t_philo **lst, t_philo *new)
{
	t_philo	*last;

	if (*lst)
	{
		new->head = *lst;
		last = get_last_philo(*lst);
		last->next = new;
		new->prev = last;
		new->next = *lst;
		(*lst)->prev = new;
	}
	else
	{
		*lst = new;
		new->head = new;
	}
}

int	init(t_sim *data, int argc, char **argv)
{
	int	i;

	i = 0;
	data->number = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_per_philo = ft_atoi(argv[5]);
	else
		data->meals_per_philo = 0;
	while (i < data->number)
	{
		lstadd_philo(&data->philo, create_philo(i));
		i++;
	}
	return (0);
}
