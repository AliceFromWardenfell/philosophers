/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 02:41:33 by alisa             #+#    #+#             */
/*   Updated: 2021/09/14 15:41:38 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/time.h>

# define OK 0
# define ERROR 1
# define FALSE 0
# define TRUE 1

typedef struct s_info
{
	int		num_of_philos; //yes
	// int		num_of_pathologists;
	// int		num_of_nutritionists;
	int		time_to_die; //yes
	int		time_to_eat; //yes
	int		time_to_sleep; //yes
	int		num_of_meals; //yes
	// int		num_of_full_philos;
	// int		num_of_finished_meals;
	// int		somebody_died;
}			t_info;

typedef struct s_philo
{
	// int				curr_num_of_meals;
	// int				is_full;
	// long			last_meal_time;
	// struct timeval	birth_time;
}			t_philo;

typedef struct s_main
{
	// pthread_t		*thread;
	// pthread_t		waiter;
	// pthread_t		*pathologist;
	// pthread_t		*nutritionist;
	// pthread_mutex_t	*mutex_fork;
	// pthread_mutex_t	*mutex_philo;
	// pthread_mutex_t	*mutex_ctrl;
	pid_t			*philo;
	sem_t			*name;
	struct s_info	info;
	// struct s_philo	*philo;
}					t_main;

int			parser(t_main *m, int argc, char **argv);

// int			philosophers_birth(t_main *m);
// int			philo_eats(t_main *m, int philo_name, int left, int right);
// int			waiter_birth(t_main *m);
// int			pathologists_birth(t_main *m);
// int			nutritionists_birth(t_main *m);
// int			print_status(t_main *m, int philo_name, char *status, int flag);
// long		curr_timestamp(t_main *m, int philo_name);
// int			smb_died(t_main *m);
// int			all_full(t_main *m);
// int			unlock_all_philo(t_main *m, int expected_amount_of_meals);
// int			wait_threads(t_main *m);
// int			destroy_mutexes(t_main *m);
// void		mem_free(t_main *m);
int			print_error(char *str);
// int			error_exit(t_main *m);
// int			critical_exit(t_main *m);
// void		*critical_exit_v(t_main *m);
long int	ft_atoi(const char *str);

#endif