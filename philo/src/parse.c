/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:51:15 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/01 16:18:22 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

unsigned long	ft_atoi(char *str)
{
	unsigned long	result;
	int				sign;

	sign = 1;
	result = 0;
	if (!str)
		exit(ft_error(ATOI_FAIL));
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	parsing_is_valid(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (ft_error(ARG_COUNT));
	argv++;
	while (*argv)
	{
		i = 0;
		while ((*argv)[i])
		{
			if (!is_digit((*argv)[i]))
				return (ft_error(INVALID_ARG));
			i++;
		}
		if (ft_atoi(*argv) > INT_MAX)
			return (ft_error(INVALID_ARG));
		argv++;
	}
	return (0);
}
