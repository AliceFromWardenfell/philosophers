/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:07:15 by alisa             #+#    #+#             */
/*   Updated: 2021/09/14 19:17:59 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_thinks(t_main *m, int philo_name)
{
	if (print_status(m, philo_name, "is thinking", NOT_EAT))
		return (ERROR);
	return (OK);
}

static int	philo_sleeps(t_main *m, int philo_name)
{
	if (print_status(m, philo_name, "is sleeping", NOT_EAT))
		return (ERROR);
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