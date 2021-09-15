/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 02:41:33 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 20:08:12 by alisa            ###   ########.fr       */
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
# include <sys/types.h>
# include <signal.h>

# define OK 0
# define ERROR 1
# define FALSE 0
# define TRUE 1
# define EAT 1
# define NOT_EAT 0
# define DIED 2
# define FULL 2

typedef struct s_info
{
	int		num_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_meals;
	int		somebody_died;
}			t_info;

typedef struct s_philo
{
	long			last_meal_time;
	struct timeval	birth_time;
}			t_philo;

typedef struct s_main
{
	pthread_t		killer;
	pid_t			*pid;
	sem_t			*forks;
	sem_t			*alive;
	sem_t			*print;
	sem_t			*kill;
	sem_t			*table;
	sem_t			*gluttony;
	struct s_info	info;
	struct s_philo	*philo;
	pthread_t		pathologist;
	int				name;
	int				curr_num_of_meals;
}					t_main;

int			parser(t_main *m, int argc, char **argv);
int			philo_eats(t_main *m, int philo_name);
int			philosophers_birth(t_main *m);
void		*pathologist(void *arg);
int			killer_birth(t_main *m);
int			print_status(t_main *m, int philo_name, char *status, int flag);
long		curr_timestamp(t_main *m, int philo_name);
int			print_error(char *str);
void		clean(t_main *m);
long int	ft_atoi(const char *str);

#endif