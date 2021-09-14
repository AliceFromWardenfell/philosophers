/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:03:46 by alisa             #+#    #+#             */
/*   Updated: 2021/09/14 19:17:20 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initialization(t_main *m)
{
	int		i;

	i = -1;
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
	if (sem_unlink("forks"))
		print_error("sem_unlink");
	if (sem_unlink("table"))
		print_error("sem_unlink");
	m->forks = sem_open("forks", O_CREAT, 0644, m->info.num_of_philos);
	if (m->forks == SEM_FAILED)
		return (print_error("semaphore opening failed"));
	m->table = sem_open("table", O_CREAT, 0644, 1);
	if (m->table == SEM_FAILED)
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
	if (sem_unlink("forks"))
		print_error("sem_unlink");
	if (sem_unlink("table"))
		print_error("sem_unlink");
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
	if (philosophers_birth(&m))
		return (ERROR);
	if (philos_wait(&m))
		return (ERROR);
	clean(&m);
	printf("OK\n");
	return (OK);
}