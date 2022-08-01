/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:19:59 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/01 16:18:52 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(int error)
{
	if (error == ARG_COUNT)
		write(2, "Invalid number of arguments\n", 28);
	if (error == INVALID_ARG)
		write(2, "Invalid argument(s)\n", 20);
	if (error == ATOI_FAIL)
		write(2, "Atoi failed\n", 12);
	if (error == INIT_ERROR)
		write(2, "Initialization failed\n", 22);
	if (error == MALLOC_ERROR)
		write(2, "Malloc failed\n", 14);
	return (EXIT_FAILURE);
}
