/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:06:57 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/10 15:19:11 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*print_hello(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld: Hello, I am philosopher n. %d\n", get_time(philo->sim), philo->nb);
	printf("%ld: Bye bye, philosopher n. %d\n", get_time(philo->sim), philo->nb);
	pthread_mutex_unlock(&philo->sim->print);
	return (NULL);
}

void	*start(void *ptr)
{
	t_sim	*data;
	t_philo	*first;
	t_philo	*current;

	data = (t_sim *)ptr;
	gettimeofday(&data->t0, NULL);
	if (pthread_mutex_init(&data->print, NULL))
		printf("Mutex init failed\n");
	first = data->head;
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
	return (NULL);
}

void	*eat(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->fork);
	printf("%ld: %d has taken a fork\n", get_time(philo->sim), philo->nb);
	if (philo->next)
		pthread_mutex_lock(&philo->next->fork);
	else
		pthread_mutex_lock(&philo->sim->head->fork);
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld: %d has taken a fork\n", get_time(philo->sim), philo->nb);
	printf("%ld: %d is eating\n", get_time(philo->sim), philo->nb);
	pthread_mutex_unlock(&philo->sim->print);
	usleep(philo->sim->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	if (philo->next)
		pthread_mutex_unlock(&philo->next->fork);
	else
		pthread_mutex_unlock(&philo->sim->head->fork);
	return (NULL);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld: %d is thinking\n", get_time(philo->sim), philo->nb);
	pthread_mutex_unlock(&philo->sim->print);
}

void	phil_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->print);
	printf("%ld: %d is sleeping\n", get_time(philo->sim), philo->nb);
	usleep(philo->sim->time_to_sleep * 1000);
	pthread_mutex_unlock(&philo->sim->print);
}

// void	execute(void *ptr)
// {
// 	t_sim 	*data;

// 	data = (t_sim *)ptr;
// 	gettimeofday(&data->t0, NULL);
// 	while (philo_hungry && !dead_philo)
// 	{
// 		if ()
// 	}
// }

