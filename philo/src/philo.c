/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:06:57 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/04 15:21:48 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void* eat(t_sim *data, t_philo *philo)
{
	struct timeval	start;

    pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->next->fork);
	gettimeofday(&start, NULL);
    printf("%ld %d is eating\n", start.tv_usec * 1000, philo->nb);
	usleep(data->time_to_eat / 1000);
    pthread_mutex_unlock(&philo->fork);
  	pthread_mutex_unlock(&philo->next->fork);
    return (NULL);
}
