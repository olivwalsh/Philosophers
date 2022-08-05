/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:14:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/05 16:03:11 by owalsh           ###   ########.fr       */
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
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef	struct s_philosopher
{
	int						nb;
	pthread_t				id;
	struct s_philosopher	*prev;
	struct s_philosopher	*next;
	struct s_philosopher	*head;
	pthread_mutex_t 		fork;
}				t_philo;

typedef struct s_simulation
{
	int				number;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_per_philo;
	pthread_mutex_t	print;
	t_philo			*philo;
	t_philo			*tmp;
}				t_sim;

/* ***** parse.c ***** */
unsigned long	ft_atoi(char *str);
int				is_digit(char c);
int				parsing_is_valid(int argc, char **argv);

/* ***** init.c ***** */
int				init(t_sim *data, int argc, char **argv);

/* ***** philo.c ***** */
void			start(t_sim *data);

/* ***** utils.c ***** */
void			display_simulation(t_sim *data);
void			*ft_memset(void *s, int c, size_t n);
t_philo			*get_last_philo(t_philo *first);

/* ***** error.c ***** */
int				ft_error(int error);

/* ***** exit.c ***** */
void			clean(t_sim *data);

#endif
