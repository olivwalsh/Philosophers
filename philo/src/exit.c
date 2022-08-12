/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:40:39 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/12 11:03:24 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_sim *data)
{
	t_philo	*philo;
	t_philo	*ptr;

	ptr = NULL;
	if (data->head)
	{
		philo = data->head;
		while (philo)
		{
			ptr = philo;
			philo = philo->next;
			free(ptr);
		}
	}
}
