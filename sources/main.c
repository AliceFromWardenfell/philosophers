/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 02:41:07 by alisa             #+#    #+#             */
/*   Updated: 2021/09/10 03:49:24 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_main *m)
{
	int				i;

	m->mutex_fork = malloc(m->info.num_of_philos * sizeof(*m->mutex_fork));
	m->mutex_philo = malloc(m->info.num_of_philos * sizeof(*m->mutex_philo));
	i = -1;
	while (++i < m->info.num_of_philos)
	{
		pthread_mutex_init(&m->mutex_fork[i], NULL);
		pthread_mutex_init(&m->mutex_philo[i], NULL);
		pthread_mutex_lock(&m->mutex_philo[i]);
	}
	m->mutex_ctrl = malloc(2 * sizeof(*m->mutex_ctrl));
	i = -1;
	while (++i < 2)
		pthread_mutex_init(&m->mutex_ctrl[i], NULL);
}

void	initialization(t_main *m)
{
	m->info.num_of_philos = NUMBER_OF_PHILOSOPHERS;
	m->info.time_to_die = TIME_TO_DIE;
	m->info.time_to_eat = TIME_TO_EAT;
	m->info.time_to_sleep = TIME_TO_SLEEP;
	m->info.num_of_meals = NUMBER_OF_TIME_EACH_PHILOSOPHER_MUST_EAT;
	m->info.free_name = -1;
	m->info.num_of_pathologists = m->info.num_of_philos / (20 + 1) + 1;
	m->info.somebody_died = FALSE;
	if (m->info.num_of_philos % 2 == 0)
		m->info.num_of_finished_meals = m->info.num_of_philos / 2;
	else
		m->info.num_of_finished_meals = 1;
	m->thread = malloc(m->info.num_of_philos * sizeof(*m->thread));
	m->pathologist = malloc(m->info.num_of_pathologists * sizeof(*m->pathologist));
	init_mutexes(m);
}

int	main(void)
{
	t_main			m;
	int				i;

	initialization(&m);
	doctors(&m);
	usleep(3000000);
	philos_birth(&m);
	waiter_birth(&m);
	while (TRUE)
		usleep(100);
	i = -1;
	while (++i < m.info.num_of_philos)
		pthread_mutex_destroy(&m.mutex_fork[i]);
	i = -1;
	while (++i < 2)
		pthread_mutex_destroy(&m.mutex_ctrl[i]);
	i = -1;
	while (++i < m.info.num_of_philos)
		pthread_join(m.thread[i], NULL);
	// free(m.philo);
	free(m.mutex_fork);
	free(m.mutex_ctrl);
	free(m.thread);
	return (0);
}
// pthread_mutex_init(&m.locks[i], NULL);
// pthread_create(&t1[i], NULL, &philo_life, (void *)&m);
// pthread_join(t1[i], NULL);