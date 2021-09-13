/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 07:21:16 by alisa             #+#    #+#             */
/*   Updated: 2021/09/13 13:27:58 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_sleeps(t_main *m, int philo_name)
{
	if (pthread_mutex_lock(&m->mutex_ctrl[ALIVE]))
		return (critical_exit(m));
	if (!(smb_died(m) == TRUE || all_full(m) == TRUE))
		if (print_status(m, philo_name, "is sleeping", NOT_EAT))
			return (ERROR);
	if (pthread_mutex_unlock(&m->mutex_ctrl[ALIVE]))
		return (critical_exit(m));
	if (usleep(m->info.time_to_sleep))
		return (critical_exit(m));
	return (OK);
}

static int	philo_thinks(t_main *m, int philo_name)
{
	if (pthread_mutex_lock(&m->mutex_ctrl[ALIVE]))
		return (critical_exit(m));
	if (!(smb_died(m) == TRUE || all_full(m) == TRUE))
		if (print_status(m, philo_name, "is thinking", NOT_EAT))
			return (ERROR);
	if (pthread_mutex_unlock(&m->mutex_ctrl[ALIVE]))
		return (critical_exit(m));
	return (OK);
}

void	*philo_life(void *arg)
{
	t_main	*m;
	int		philo_name;
	int		left;
	int		right;

	m = (t_main *)arg;
	if (pthread_mutex_lock(&m->mutex_ctrl[NAME]))
		return (critical_exit_v(m));
	philo_name = ++m->info.free_name;
	if (pthread_mutex_unlock(&m->mutex_ctrl[NAME]))
		return (critical_exit_v(m));
	left = philo_name % m->info.num_of_philos;
	right = philo_name - 1;
	if (gettimeofday(&m->philo[philo_name - 1].birth_time, NULL))
		return (critical_exit_v(m));
	while (TRUE)
	{
		if (philo_eats(m, philo_name, left, right))
			return (NULL);
		if (philo_sleeps(m, philo_name))
			return (NULL);
		if (philo_thinks(m, philo_name))
			return (NULL);
	}
	return (NULL);
}

int	philosophers_birth(t_main *m)
{
	int		i;

	i = -1;
	while (++i < m->info.num_of_philos)
		if (pthread_create(&m->thread[i], NULL, &philo_life, (void *)m))
			return (ERROR);
	return (OK);
}
