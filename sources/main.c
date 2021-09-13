/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 02:41:07 by alisa             #+#    #+#             */
/*   Updated: 2021/09/13 13:16:25 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_main *m)
{
	int				i;

	i = -1;
	while (++i < m->info.num_of_philos)
	{
		if (pthread_mutex_init(&m->mutex_fork[i], NULL))
			return (error_exit(m));
		if (pthread_mutex_init(&m->mutex_philo[i], NULL))
			return (error_exit(m));
		if (pthread_mutex_lock(&m->mutex_philo[i]))
			return (error_exit(m));
	}
	i = -1;
	while (++i < 4)
		if (pthread_mutex_init(&m->mutex_ctrl[i], NULL))
			return (error_exit(m));
	return (OK);
}

static int	allocations(t_main *m)
{
	int	i;

	m->mutex_fork = malloc(m->info.num_of_philos * sizeof(*m->mutex_fork));
	m->mutex_philo = malloc(m->info.num_of_philos * sizeof(*m->mutex_philo));
	m->mutex_ctrl = malloc(4 * sizeof(*m->mutex_ctrl));
	m->philo = malloc(m->info.num_of_philos * sizeof(*m->philo));
	m->thread = malloc(m->info.num_of_philos * sizeof(*m->thread));
	m->pathologist = malloc(m->info.num_of_pathologists * sizeof(pthread_t));
	m->nutritionist = malloc(m->info.num_of_nutritionists * sizeof(pthread_t));
	if (m->mutex_fork == NULL || m->mutex_philo == NULL
		|| m->mutex_ctrl == NULL || m->philo == NULL || m->thread == NULL
		|| m->pathologist == NULL || m->nutritionist == NULL)
		return (error_exit(m));
	i = -1;
	while (++i < m->info.num_of_philos)
	{
		m->philo[i].last_meal_time = 0;
		m->philo[i].is_full = FALSE;
		m->philo[i].curr_num_of_meals = 0;
		if (gettimeofday(&m->philo[i].birth_time, NULL))
			return (error_exit(m));
	}
	return (OK);
}

int	initialization(t_main *m)
{
	m->info.num_of_full_philos = 0;
	m->info.free_name = 0;
	m->info.free_name_p = -1;
	m->info.free_name_n = -1;
	m->info.num_of_pathologists = m->info.num_of_philos / (20 + 1) + 1;
	m->info.num_of_nutritionists = m->info.num_of_pathologists;
	m->info.somebody_died = FALSE;
	m->mutex_ctrl = NULL;
	m->mutex_fork = NULL;
	m->mutex_philo = NULL;
	m->pathologist = NULL;
	m->nutritionist = NULL;
	m->philo =  NULL;
	m->thread = NULL;
	if (m->info.num_of_philos % 2 == 0)
		m->info.num_of_finished_meals = m->info.num_of_philos / 2;
	else
		m->info.num_of_finished_meals = 1;
	if (allocations(m))
		return (ERROR);
	if (init_mutexes(m))
		return (ERROR);
	return (OK);
}

int	main(int argc, char **argv) // check error cases for leaks
{
	t_main			m;

	if (parser(&m, argc, argv))
		return (ERROR);
	if (initialization(&m))
		return (ERROR);
	if (pathologists_birth(&m))
		return (ERROR);
	if (philosophers_birth(&m))
		return (ERROR);
	if (m.info.num_of_meals != -1)
		if (nutritionists_birth(&m))
			return (ERROR);
	if (waiter_birth(&m))
		return (ERROR);
	
	wait_threads(&m);
	destroy_mutexes(&m);
	mem_free(&m);
	return (OK);
}
