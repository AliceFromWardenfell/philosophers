/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:07:15 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 09:12:59 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_still_alive(t_main *m, int philo_name)
{
	long		timestamp;
	
	if (sem_wait(m->print))
		return (print_error("sem_wait: print"));
	// printf ("dc: print--\n");
	timestamp = curr_timestamp(m, philo_name);
	if (timestamp == -1)
		return (ERROR);
	// printf("%ld %ld %d\n", timestamp, m->philo[philo_name - 1].last_meal_time, m->info.time_to_die);
	if (timestamp - m->philo[philo_name - 1].last_meal_time
		>= m->info.time_to_die)
	{
		if (print_status(m, philo_name, "\033[31mdied\033[0m", NOT_EAT))
			return (ERROR);
		if (sem_post(m->kill))
			return (print_error("sem_post"));
		return (DIED);
	}
	if (sem_post(m->print))
		return (print_error("sem_post: print"));
	// printf ("dc: print++\n");
	return (OK);
}	

static int	philo_thinks(t_main *m, int philo_name)
{
	if (check_if_still_alive(m, philo_name))
		return (ERROR);
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
	if (check_if_still_alive(m, philo_name))
		return (ERROR);
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
	if (gettimeofday(&m->philo[philo_name - 1].birth_time, NULL))
		return (ERROR);
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
	int		i;

	i = -1;
	while (++i < m->info.num_of_philos)
	{
		m->pid[i] = fork();
		if (m->pid[i] == -1)
			return (print_error("can not create process"));
		if (!m->pid[i])
			return (philo_life(m, i + 1));
	}
	return (OK);
}