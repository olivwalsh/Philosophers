/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:13:41 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/01 16:25:08 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_sim	data;

	ft_memset(&data, 0, sizeof(t_sim));
	if (parsing_is_valid(argc, argv))
		return (EXIT_FAILURE);
	if (init(&data, argc, argv))
		return (ft_error(INIT_ERROR));
	display_simulation(&data);
	return (EXIT_SUCCESS);
}
