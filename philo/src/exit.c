/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:40:39 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/12 15:42:00 by owalsh           ###   ########.fr       */
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
		while (i < data->number)
		{
			ptr = philo;
			philo = philo->next;
			free(ptr);
			i++;
		}
	}
}
