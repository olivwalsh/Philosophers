/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:13:41 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/16 16:58:05 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_sim	data;
	int		error;

	memset(&data, 0, sizeof(t_sim));
	if (parsing_is_valid(argc, argv))
		return (EXIT_FAILURE);
	if (init(&data, argc, argv))
		return (ft_error(INIT_ERROR));
	error = execute(&data);
	clean(&data);
	if (error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
