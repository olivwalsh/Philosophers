/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:13:41 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/01 16:18:47 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	ft_memset(&philo, 0, sizeof(t_philo));
	if (parsing_is_valid(argc, argv))
		return (EXIT_FAILURE);
	if (init(&philo, argc, argv))
		return (ft_error(INIT_ERROR));
	display_philo(&philo);
	return (EXIT_SUCCESS);
}
