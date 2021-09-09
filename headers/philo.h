/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 02:41:33 by alisa             #+#    #+#             */
/*   Updated: 2021/09/10 01:51:09 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

# define NUMBER_OF_PHILOSOPHERS 5
# define TIME_TO_DIE 800
# define TIME_TO_EAT 200
# define TIME_TO_SLEEP 200
# define NUMBER_OF_TIME_EACH_PHILOSOPHER_MUST_EAT 7

# define NAME 0
# define MEAL 1

# define TRUE 1

typedef struct s_info
{
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_meals;
	int		free_name;
	int		num_of_finished_meals;
}			t_info;

// typedef struct s_philo
// {
// 	int			name;
// }				t_philo;

typedef struct s_main
{
	pthread_t		*thread;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	*mutex_philo;
	pthread_mutex_t	*mutex_ctrl;
	// struct s_philo	*philo;
	struct s_info	info;
}					t_main;

void	philos_birth(t_main *m);
void	waiter(t_main *m);
int		error(void);

#endif