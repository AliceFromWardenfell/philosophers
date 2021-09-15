/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:03:46 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 19:55:54 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initialization(t_main *m)
{
	int		i;

	i = -1;
	
	m->name = 0;
	m->info.somebody_died = FALSE;
	m->pid = NULL;
	m->philo = NULL;
	m->pid = malloc(m->info.num_of_philos * sizeof(pid_t));
	m->philo = malloc(m->info.num_of_philos * sizeof(*m->philo));
	if (!m->pid || !m->philo)
		return (kill(0, SIGTERM));
	while (++i < m->info.num_of_philos)
	{
		if (gettimeofday(&m->philo[i].birth_time, NULL))
			return (kill(0, SIGTERM));
		m->philo[i].last_meal_time = 0;
		m->curr_num_of_meals = 0;
		m->pid[i] = 0;
	}
	return (OK);
}

static int	semaphores_initialization(t_main *m)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("kill");
	sem_unlink("table");
	m->forks = sem_open("forks", O_CREAT, 0644, m->info.num_of_philos);
	if (m->forks == SEM_FAILED)
		return (kill(0, SIGTERM));
	m->print = sem_open("print", O_CREAT, 0644, 1);
	if (m->print == SEM_FAILED)
		return (kill(0, SIGTERM));
	m->kill = sem_open("kill", O_CREAT, 0644, 0);
	if (m->print == SEM_FAILED)
		return (kill(0, SIGTERM));
	m->table = sem_open("table", O_CREAT, 0644, 1);
	if (m->print == SEM_FAILED)
		return (kill(0, SIGTERM));
	return (OK);
}

static int	semaphores_close(t_main *m)
{
	if (sem_close(m->forks))
		return (ERROR);
	if (sem_close(m->print))
		return (ERROR);
	if (sem_close(m->kill))
		return (ERROR);
	if (sem_close(m->table))
		return (ERROR);
	return (OK);
}

static int	philos_wait(t_main *m)
{
	int		i;

	i = -1;
	while (++i < m->info.num_of_philos)
		if (waitpid(m->pid[i], NULL, 0) == -1)
			return (kill(0, SIGTERM));
	return (OK);
}

int	main(int argc, char **argv)
{
	t_main m;

	if (parser(&m, argc, argv))
		return (ERROR);
	if (initialization (&m))
		return (ERROR);
	if (semaphores_initialization(&m))
		return (ERROR);
	if (killer_birth(&m))
		return (ERROR);
	if (philosophers_birth(&m))
		return (ERROR);
	if (philos_wait(&m))
		return (ERROR);
	if (pthread_detach(m.killer))
		return (ERROR);
	if (semaphores_close(&m))
		return (ERROR);
	clean(&m);
	return (OK);
}