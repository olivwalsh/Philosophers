/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:14:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/18 11:30:46 by owalsh           ###   ########.fr       */
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

struct	s_simulation;

typedef struct s_philosopher
{
	int						nb;
	pthread_t				id;
	struct s_philosopher	*prev;
	struct s_philosopher	*next;
	struct s_philosopher	*head;
	pthread_mutex_t			fork;
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
	pthread_mutex_t	death;
	t_philo			*head;
	struct timeval	t0;
}				t_sim;

/*
**
** parse.c
**
*/
unsigned long	ft_atoi(char *str);
int				is_digit(char c);
int				parsing_is_valid(int argc, char **argv);

/*
**
** init.c
**
*/
int				init(t_sim *data, int argc, char **argv);

/*
**
** philo.c 
**
*/
int				execute(t_sim *data);
void			*philo_life(void *ptr);

/*
**
** philo_2.c
** 
*/
void			*check_end(void *ptr);
int				check_is_full(t_philo *philo);
int				check_meals_count(t_philo *philo);
int				check_sim_end(t_philo *philo);
int				is_dead(t_philo *philo);

/*
**
** utils.c
**
*/
t_philo			*get_last_philo(t_philo *first);
long long		last_time_eaten(t_philo *philo);;
void			printlog(t_philo *philo, char *str);
long long		timediff(struct timeval t0, struct timeval now);
struct	timeval	timestamp(void);

/*
**
** error.c
**
*/
int				ft_error(int error);

/*
**
** exit.c
**
*/
void			clean(t_sim *data);
int				exitsim(t_sim *data);

#endif
