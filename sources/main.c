/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 02:41:07 by alisa             #+#    #+#             */
/*   Updated: 2021/09/12 07:14:34 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_main *m)
{
	int				i;

	i = -1;
	while (++i < m->info.num_of_philos)
	{
		pthread_mutex_init(&m->mutex_fork[i], NULL);
		pthread_mutex_init(&m->mutex_philo[i], NULL);
		pthread_mutex_lock(&m->mutex_philo[i]);
	}
	i = -1;
	while (++i < 3)
	{
		if (pthread_mutex_init(&m->mutex_ctrl[i], NULL))
			printf("INIT_ERROR!\n");
	}
}

void	allocations(t_main *m)
{
	int	i;

	m->mutex_fork = malloc(m->info.num_of_philos * sizeof(*m->mutex_fork));
	m->mutex_philo = malloc(m->info.num_of_philos * sizeof(*m->mutex_philo));
	m->mutex_ctrl = malloc(3 * sizeof(*m->mutex_ctrl));
	m->philo = malloc(m->info.num_of_philos * sizeof(*m->philo));
	m->thread = malloc(m->info.num_of_philos * sizeof(*m->thread));
	m->pathologist = malloc(m->info.num_of_pathologists * sizeof(pthread_t));
	i = -1;
	while (++i < m->info.num_of_philos)
	{
		m->philo[i].last_meal_time = 0;
		m->philo[i].curr_num_of_meals = 0;
		gettimeofday(&m->philo[i].birth_time, NULL);
	}
}

void	initialization(t_main *m)
{
	m->info.num_of_philos = NUMBER_OF_PHILOSOPHERS;
	m->info.time_to_die = TIME_TO_DIE;
	m->info.time_to_eat = TIME_TO_EAT * 1000;
	m->info.time_to_sleep = TIME_TO_SLEEP * 1000;
	m->info.num_of_meals = NUMBER_OF_TIME_EACH_PHILOSOPHER_MUST_EAT;
	m->info.free_name = 0;
	m->info.free_name_ = -1;
	m->info.num_of_pathologists = m->info.num_of_philos / (20 + 1) + 1;
	m->info.somebody_died = FALSE;
	m->mutex_ctrl = NULL;
	m->mutex_fork = NULL;
	m->mutex_philo = NULL;
	m->pathologist = NULL;
	m->philo =  NULL;
	m->thread = NULL;
	if (m->info.num_of_philos % 2 == 0)
		m->info.num_of_finished_meals = m->info.num_of_philos / 2;
	else
		m->info.num_of_finished_meals = 1;
	allocations(m);
	init_mutexes(m);
}

int	main(void)
{
	t_main			m;
	int				i;

	initialization(&m);
	pathologist_birth(&m);
	philos_birth(&m);
	waiter_birth(&m);
	// while (TRUE)
	// 	usleep(1000000);
	i = -1;
	while (++i < m.info.num_of_philos)
		pthread_join(m.thread[i], NULL);
	i = -1;
	while (++i < m.info.num_of_pathologists)
		pthread_join(m.pathologist[i], NULL);
	i = -1;
	while (++i < m.info.num_of_philos)
		pthread_mutex_destroy(&m.mutex_fork[i]);
	i = -1;
	while (++i < m.info.num_of_philos)
		pthread_mutex_destroy(&m.mutex_philo[i]);
	i = -1;
	while (++i < 2)
		pthread_mutex_destroy(&m.mutex_ctrl[i]);
	// free(m.philo);
	free(m.mutex_fork);
	free(m.mutex_ctrl);
	free(m.thread);
	return (0);
}
// pthread_mutex_init(&m.locks[i], NULL);
// pthread_create(&t1[i], NULL, &philo_life, (void *)&m);
// pthread_join(t1[i], NULL);