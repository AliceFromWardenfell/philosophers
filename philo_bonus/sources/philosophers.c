/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:07:15 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 17:00:12 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	check_if_still_alive(t_main *m, int philo_name)
// {
	
// }

static int	philo_thinks(t_main *m, int philo_name)
{
	// if (check_if_still_alive(m, philo_name))
	// 	return (ERROR);
	if (sem_wait(m->print))
		return (print_error("sem_wait: print"));
	// printf ("t: print--\n");
	if (print_status(m, philo_name, "is thinking", NOT_EAT))
		return (ERROR);
	if (sem_post(m->print))
		return (print_error("sem_post: print"));
	// printf ("t: print++\n");
	return (OK);
}

static int	philo_sleeps(t_main *m, int philo_name)
{
	// if (check_if_still_alive(m, philo_name))
	// 	return (ERROR);
	if (sem_wait(m->print))
		return (print_error("sem_wait: print"));
	// printf ("s: print--\n");
	if (print_status(m, philo_name, "is sleeping", NOT_EAT))
		return (ERROR);
	if (sem_post(m->print))
		return (print_error("sem_post: print"));
	// printf ("s: print++\n");
	if (usleep(m->info.time_to_sleep))
		return (ERROR);
	return (OK);
}

static int	philo_life(t_main *m, int philo_name)
{
	m->name = philo_name;
	if (pthread_create(&m->pathologist, NULL,
		&pathologist, (void *)m))
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
		return (ERROR);
	while (++i < m->info.num_of_philos)
	{
		m->philo[i].birth_time = sim_start;
		m->pid[i] = fork();
		if (m->pid[i] == -1)
			return (print_error("can not create process"));
		if (!m->pid[i])
			return (philo_life(m, i + 1));
	}
	return (OK);
}
