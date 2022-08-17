/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:40:39 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/17 16:52:27 by owalsh           ###   ########.fr       */
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
		while (i < data->number && philo)
		{
			ptr = philo;
			philo = philo->next;
			if (ptr)
				free(ptr);
			i++;
		}
	}
}

int	exitsim(t_sim *data)
{
	t_philo	*current;
	int		i;
	// int		j;
	// int		error;
	int		exit_status;

	current = data->head;
	i = 0;
	while (i < data->number && current)
	{
		waitpid(current->pid, &exit_status, 0);
		// if (WIFEXITED(exit_status))
		// {
		// 	error = WEXITSTATUS(exit_status);
		// 	j = 0;
		// 	while (i < data->number)
		// 	{
		// 		kill(current->pid, SIGTERM);
		// 		j++;
		// 	}
		// }
		// if (error)
		// 	return (error);
		current = current->next;
		i++;
	}
	return (EXIT_SUCCESS);
}
