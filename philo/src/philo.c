/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:06:57 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/05 16:27:33 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void*	eat(t_sim *data, t_philo *philo)
// {
// 	struct timeval	start;

//     pthread_mutex_lock(&philo->fork);
// 	pthread_mutex_lock(&philo->next->fork);
// 	gettimeofday(&start, NULL);
//     printf("%ld %d is eating\n", start.tv_usec * 1000, philo->nb);
// 	usleep(data->time_to_eat / 1000);
//     pthread_mutex_unlock(&philo->fork);
//   	pthread_mutex_unlock(&philo->next->fork);
//     return (NULL);
// }

void	*print_hello(void *ptr)
{
	t_sim	*data;

	data = (t_sim *)ptr;
	pthread_mutex_lock(&data->print);
	printf("Hello, I am philosopher n. %d\n", data->tmp->nb);
	printf("Bye bye, philosopher n. %d\n", data->tmp->nb);
	pthread_mutex_unlock(&data->print);
	return (NULL);
}

void	start(t_sim *data)
{
	int		i;

	if (pthread_mutex_init(&data->print, NULL))
		printf("Mutex init failed\n");
	i = 0;
	data->tmp = data->philo;
	while (i < data->number)
	{
		pthread_create(&data->tmp->id, NULL, &print_hello, data);
		data->tmp = data->tmp->next;
		i++;
	}
	i = 0;
	data->tmp = data->philo;
	while (i < data->number)
	{
		pthread_join(data->tmp->id, NULL);
		data->tmp = data->tmp->next;
		i++;
	}
	pthread_mutex_destroy(&data->print);
}
