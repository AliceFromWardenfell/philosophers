/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 02:41:33 by alisa             #+#    #+#             */
/*   Updated: 2021/09/12 11:23:02 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h> //?
# include <string.h> //?

# define NUMBER_OF_PHILOSOPHERS 44
# define TIME_TO_DIE 130
# define TIME_TO_EAT 60
# define TIME_TO_SLEEP 60
# define NUMBER_OF_TIME_EACH_PHILOSOPHER_MUST_EAT 7

# define NAME 0
# define MEAL 1
# define ALIVE 2

# define OK 0
# define ERROR 1
# define FALSE 0
# define TRUE 1

typedef struct s_info
{
	int		num_of_philos;
	int		num_of_pathologists;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_meals;
	int		free_name;
	int		free_name_;
	int		num_of_finished_meals;
	int		somebody_died;
}			t_info;

typedef struct s_philo
{
	int				curr_num_of_meals;
	long			last_meal_time;
	struct timeval	birth_time;
}			t_philo;

typedef struct s_main
{
	pthread_t		*thread;
	pthread_t		*pathologist;
	pthread_t		waiter;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	*mutex_philo;
	pthread_mutex_t	*mutex_ctrl;
	struct s_info	info;
	struct s_philo	*philo;
}					t_main;

int		philos_birth(t_main *m);
int		waiter_birth(t_main *m);
int		pathologist_birth(t_main *m);
int		nutritionist(t_main *m);
int		print_status(t_main *m, int philo_name, char *status);
long	curr_timestamp(t_main *m, int philo_name);
int		smb_died(t_main *m);
int		unlock_all_philo(t_main *m, int expected_amount_of_meals);
int		error(t_main *m);

#endif