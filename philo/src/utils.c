/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:26:39 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/01 16:27:57 by owalsh           ###   ########.fr       */
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

void	display_simulation(t_sim *data)
{
	printf("sim->number = %d\n", data->number);
	printf("sim->time_to_die = %d\n", data->time_to_die);
	printf("sim->time_to_eat = %d\n", data->time_to_eat);
	printf("sim->time_to_sleep = %d\n", data->time_to_sleep);
	printf("sim->meals_per_philo = %d\n", data->meals_per_philo);
}
