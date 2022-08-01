/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:14:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/01 16:23:13 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define ARG_COUNT -1
# define MALLOC_ERROR -2
# define ATOI_FAIL -3
# define INIT_ERROR -4
# define INVALID_ARG -5

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef	struct s_philosopher
{
	
}				t_philo;

typedef struct s_simulation
{
	int	number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_per_philo;
}				t_sim;

/* ***** parse.c ***** */
unsigned long	ft_atoi(char *str);
int				is_digit(char c);
int				parsing_is_valid(int argc, char **argv);

/* ***** init.c ***** */
int				init(t_sim *data, int argc, char **argv);

/* ***** utils.c ***** */
void			display_simulation(t_sim *data);
void			*ft_memset(void *s, int c, size_t n);

/* ***** error.c ***** */
int				ft_error(int error);

#endif
