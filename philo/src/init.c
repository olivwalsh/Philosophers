/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:28:17 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/04 13:31:14 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	add_new_philo(t_philo **begin_list, t_philo *new)
// {
// 	while (*begin_list)
// 	{
// 		(*begin_list)++;
// 	}
	
// }

int	init(t_sim *data, int argc, char **argv)
{
	// int	i;

	// i = 0;
	data->number = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_per_philo = ft_atoi(argv[5]);
	else
		data->meals_per_philo = 0;
	// while (i < data->number)
	// {
	// 	add_new_philo(data->philos, create_philo());
	// 	i++;
	// }
	return (0);
}
