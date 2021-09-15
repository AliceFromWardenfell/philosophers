/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:03:46 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 15:54:37 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initialization(t_main *m)
{
	int		i;

	i = -1;
	
	m->name = 0;
	m->info.somebody_died = FALSE;
	m->pid = malloc(m->info.num_of_philos * sizeof(pid_t));
	m->philo = malloc(m->info.num_of_philos * sizeof(*m->philo));
	while (++i < m->info.num_of_philos)
	{
		if (gettimeofday(&m->philo[i].birth_time, NULL))
			return (ERROR);
		m->philo[i].last_meal_time = 0;
		m->pid[i] = 0;
	}
	return (OK);
}

int	semaphores_initialization(t_main *m)
{
	sem_unlink("forks");
	sem_unlink("alive");
	sem_unlink("print");
	sem_unlink("kill");
	sem_unlink("table");
	m->forks = sem_open("forks", O_CREAT, 0644, m->info.num_of_philos);
	if (m->forks == SEM_FAILED)
		return (print_error("semaphore opening failed"));
	m->alive = sem_open("alive", O_CREAT, 0644, 1);
	if (m->alive == SEM_FAILED)
		return (print_error("semaphore opening failed"));
	m->print = sem_open("print", O_CREAT, 0644, 1);
	if (m->print == SEM_FAILED)
		return (print_error("semaphore opening failed"));
	m->kill = sem_open("kill", O_CREAT, 0644, 0);
	if (m->print == SEM_FAILED)
		return (print_error("semaphore opening failed"));
	m->table = sem_open("table", O_CREAT, 0644, 1);
	if (m->print == SEM_FAILED)
		return (print_error("semaphore opening failed"));
	return (OK);
}

int	philos_wait(t_main *m)
{
	int		i;

	i = -1;
	while (++i < m->info.num_of_philos)
	{
		// kill(m->philo[i], SIGTERM);
		if (waitpid(m->pid[i], NULL, 0) == -1)
			return (print_error("waitpid"));
	}
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
	if (pthread_join(m.killer, NULL))
		return (ERROR);
	clean(&m);
	printf("OK\n");
	return (OK);
}