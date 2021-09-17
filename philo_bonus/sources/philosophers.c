/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:07:15 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 20:56:20 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_thinks(t_main *m, int philo_name)
{
	if (sem_wait(m->print))
		return (kill(0, SIGTERM));
	if (print_status(m, philo_name, "is thinking", NOT_EAT))
		return (ERROR);
	if (sem_post(m->print))
		return (kill(0, SIGTERM));
	return (OK);
}

static int	philo_sleeps(t_main *m, int philo_name)
{
	if (sem_wait(m->print))
		return (print_error("sem_wait: print"));
	if (print_status(m, philo_name, "is sleeping", NOT_EAT))
		return (ERROR);
	if (sem_post(m->print))
		return (print_error("sem_post: print"));
	if (usleep(m->info.time_to_sleep))
		return (kill(0, SIGTERM));
	return (OK);
}

static int	philo_life(t_main *m, int philo_name)
{
	m->name = philo_name;
	if (pthread_create(&m->pathologist, NULL, &pathologist, (void *)m))
		return (print_error("pathologist creation failed"));
	while (TRUE)
	{
		if (philo_eats(m, philo_name))
			return (ERROR);
		if (philo_sleeps(m, philo_name))
			return (ERROR);
		if (philo_thinks(m, philo_name))
			return (ERROR);
	}
	clean(m);
	return (2);
}

int	philosophers_birth(t_main *m)
{
	int				i;
	struct timeval	sim_start;

	i = -1;
	if (gettimeofday(&sim_start, NULL))
		return (kill(0, SIGTERM));
	while (++i < m->info.num_of_philos)
	{
		m->philo[i].birth_time = sim_start;
		m->pid[i] = fork();
		if (m->pid[i] == -1)
			return (kill(0, SIGTERM));
		if (!m->pid[i])
			return (philo_life(m, i + 1));
	}
	return (OK);
}
