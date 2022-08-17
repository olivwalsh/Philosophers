/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:26:39 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/17 11:08:16 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printlog(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->sim->print);
	if (check_sim_end(philo))
	{
		pthread_mutex_unlock(&philo->sim->print);
		return ;
	}
	printf(" %lld ", timediff(philo->sim->t0, timestamp()));
	printf("%d ", philo->nb);
	printf("%s\n", str);
	pthread_mutex_unlock(&philo->sim->print);
}

t_philo	*get_last_philo(t_philo *first)
{
	t_philo	*current;

	current = first;
	while (current->next && current->next != first)
		current = current->next;
	return (current);
}

struct	timeval	timestamp(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now);
}

long long	timediff(struct timeval t0, struct timeval now)
{
	long long	now_ms;
	long long	t0_ms;

	now_ms = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	t0_ms = (t0.tv_sec * 1000) + (t0.tv_usec / 1000);
	return (now_ms - t0_ms);
}
