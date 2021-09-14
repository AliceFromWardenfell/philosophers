/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:03:46 by alisa             #+#    #+#             */
/*   Updated: 2021/09/14 16:00:16 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_main *m)
{
	if (m->philo)
		free(m->philo);
}

static int	initialization(t_main *m)
{
	int		i;

	i = -1;
	m->philo = malloc(m->info.num_of_philos * sizeof(pid_t));
	while (++i < m->info.num_of_philos)
		m->philo[i] = 0;
	return (OK);
}

int	philo_life(t_main *m, int philo_name)
{
	if (sem_wait(m->name))
		return (print_error("sem_wait"));
	usleep(300000);
	printf("%d. My name is %d\n", m->info.num_of_philos, philo_name);
	if (sem_post(m->name))
		return (print_error("sem_post"));
	clean(m);
	return (2);
}

int	philos_birth(t_main *m)
{
	int		i;

	i = -1;
	while (++i < m->info.num_of_philos)
	{
		m->philo[i] = fork();
		if (m->philo[i] == -1)
			return (print_error("can not create process"));
		if (!m->philo[i])
			return (philo_life(m, i + 1));
	}
	return (OK);
}

int	semaphores_initialization(t_main *m)
{
	if (sem_unlink("name"))
		return (print_error("sem_unlink"));
	m->name = sem_open("name", O_CREAT, 0644, 1);
	if (m->name == SEM_FAILED)
		return (print_error("semaphore opening failed"));
	return (OK);
}

int	philos_wait(t_main *m)
{
	int		i;

	i = -1;
	while (++i < m->info.num_of_philos)
	{
		if (waitpid(m->philo[i], NULL, 0) == -1)
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
	if (philos_birth(&m))
		return (ERROR);
	if (philos_wait(&m))
		return (ERROR);
	clean(&m);
	printf("OK\n");
	return (OK);
}