/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:28:17 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/16 16:28:41 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo(int id, t_sim *data)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->nb = id;
	pthread_mutex_init(&new->fork, NULL);
	new->next = NULL;
	new->prev = NULL;
	new->sim = data;
	new->is_full = 0;
	new->meals = 0;
	memset(&new->last_meal, 0, sizeof(struct timeval));
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
	data->sim_end = 0;
	pthread_mutex_init(&data->death, NULL);
	if (argc == 6)
		data->meals_per_philo = ft_atoi(argv[5]);
	else
		data->meals_per_philo = 0;
	while (i < data->number)
	{
		lstadd_philo(&data->head, create_philo(i + 1, data));
		i++;
	}
	return (0);
}
