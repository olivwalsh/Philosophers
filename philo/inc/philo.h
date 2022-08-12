/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:14:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/12 18:20:55 by owalsh           ###   ########.fr       */
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

struct s_simulation;

typedef struct s_philosopher
{
	int						nb;
	pthread_t				id;
	struct s_philosopher	*prev;
	struct s_philosopher	*next;
	struct s_philosopher	*head;
	pthread_mutex_t			fork;
	pthread_mutex_t			last_m;
	struct s_simulation		*sim;
	int						meals;
	int						is_full;
	struct timeval			last_meal;
}				t_philo;

typedef struct s_simulation
{
	int				number;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				meals_per_philo;
	int				sim_end;
	pthread_mutex_t	print;
	t_philo			*head;
	struct timeval	t0;
}				t_sim;

/* ***** parse.c ***** */
unsigned long	ft_atoi(char *str);
int				is_digit(char c);
int				parsing_is_valid(int argc, char **argv);

/* ***** init.c ***** */
int				init(t_sim *data, int argc, char **argv);

/* ***** philo.c ***** */
void			*start(void *ptr);
int				execute(t_sim *data);
int 			exitsim(t_sim *data);
void			*philo_life(void *ptr);

/* ***** philo_2.c ***** */
int				dead_philo(t_sim *data);
int				is_dead(t_philo *philo);
int				philo_hungry(t_sim *data);

/* ***** utils.c ***** */
void			display_simulation(t_sim *data);
t_philo			*get_last_philo(t_philo *first);
void			printlog(t_philo *philo, char *str);
long long		timediff(struct timeval t0, struct timeval now);
struct	timeval	timestamp();

/* ***** error.c ***** */
int				ft_error(int error);

/* ***** exit.c ***** */
void			clean(t_sim *data);

#endif
