/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:40:39 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/17 18:09:28 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_sim *data)
{
	t_philo	*philo;
	t_philo	*ptr;
	int		i;

	ptr = NULL;
	sem_close(data->death);
	sem_close(data->print);
	sem_close(data->forks);
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("forks");
	i = 0;
	if (data->head)
	{
		philo = data->head;
		while (i < data->number && philo)
		{
			ptr = philo;
			philo = philo->next;
			free(ptr);
			i++;
		}
	}
}

int	exitsim(t_sim *data)
{
	t_philo	*current;
	int		i;
	int		exit_status;

	current = data->head;
	i = -1;
	waitpid(-1, &exit_status, 0);
	if (WEXITSTATUS(exit_status) == 1)
	{
		while (++i < data->number)
		{
			kill(current->pid, SIGTERM);
			current = current->next;
		}
	}
	else
	{
		while (++i < data->number)
		{
			waitpid(current->pid, &exit_status, 0);
			current = current->next;
		}
	}
	return (EXIT_SUCCESS);
}
