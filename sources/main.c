/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 02:41:07 by alisa             #+#    #+#             */
/*   Updated: 2021/09/06 08:46:59 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_main *m)
{
	int		i;

	m->mutex_fork = malloc(m->info.num_of_philos * sizeof(*m->mutex_fork));
	i = -1;
	while (++i < m->info.num_of_philos)
	{
		pthread_mutex_init(&m->mutex_fork[i], NULL);
		pthread_mutex_lock(&m->mutex_fork[i]);
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
	m->info.free_name = 1;
	m->philo = malloc(m->info.num_of_philos * sizeof(*m->philo));
	init_mutexes(m);
}

int	main(void)
{
	t_main		m;

	initialization(&m);
	philos_birth(&m);
	return (0);
}
// pthread_mutex_init(&m.locks[i], NULL);
// pthread_create(&t1[i], NULL, &philo_life, (void *)&m);
// pthread_join(t1[i], NULL);