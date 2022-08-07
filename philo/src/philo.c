/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:06:57 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/07 12:33:03 by owalsh           ###   ########.fr       */
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
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->sim->print);
	printf("Hello, I am philosopher n. %d\n", philo->nb);
	printf("Bye bye, philosopher n. %d\n", philo->nb);
	pthread_mutex_unlock(&philo->sim->print);
	return (NULL);
}

void	start(t_sim *data)
{
	t_philo	*first;
	t_philo	*current;

	if (pthread_mutex_init(&data->print, NULL))
		printf("Mutex init failed\n");
	first = data->philo;
	current = first;
	while (current)
	{
		pthread_create(&current->id, NULL, &print_hello, current);
		current = current->next;
	}
	current = first;
	while (current)
	{
		pthread_join(current->id, NULL);
		current = current->next;
	}
	pthread_mutex_destroy(&data->print);
}
