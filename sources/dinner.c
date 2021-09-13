/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:26:08 by alisa             #+#    #+#             */
/*   Updated: 2021/09/13 13:27:43 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	unlock_forks(t_main *m, int left, int right)
{
	if (pthread_mutex_unlock(&m->mutex_ctrl[ALIVE]))
		return (critical_exit(m));
	if (pthread_mutex_unlock(&m->mutex_fork[right]))
		return (critical_exit(m));
	if (pthread_mutex_unlock(&m->mutex_fork[left]))
		return (critical_exit(m));
	return (2);
}

static int add_meal(t_main *m)
{
	if (pthread_mutex_lock(&m->mutex_ctrl[MEAL]))
		return (critical_exit(m));
	m->info.num_of_finished_meals++;
	if (pthread_mutex_unlock(&m->mutex_ctrl[MEAL]))
		return (critical_exit(m));
	return (OK);
}

static int add_global_meal(t_main *m, int philo_name)
{
	if (pthread_mutex_lock(&m->mutex_ctrl[DIET]))
		return (critical_exit(m));
	m->philo[philo_name - 1].curr_num_of_meals++;
	if (pthread_mutex_unlock(&m->mutex_ctrl[DIET]))
		return (critical_exit(m));
	return (OK);
}

static int	take_forks(t_main *m, int philo_name, int left, int right)
{
	if (pthread_mutex_lock(&m->mutex_philo[philo_name - 1]))
		return (critical_exit(m));
	if (pthread_mutex_lock(&m->mutex_fork[right]))
		return (critical_exit(m));
	if (!(smb_died(m) == TRUE || all_full(m) == TRUE))
		if (print_status(m, philo_name, "has taken a fork", NOT_EAT))
			return (ERROR);
	if (m->info.num_of_philos == 1)
	{
		if (pthread_mutex_unlock(&m->mutex_fork[right]))
			return (critical_exit(m));
		if (pthread_mutex_unlock(&m->mutex_philo[0]))
			return (critical_exit(m));
		return (2);
	}
	if (pthread_mutex_lock(&m->mutex_fork[left]))
		return (critical_exit(m));
	if (!(smb_died(m) == TRUE || all_full(m) == TRUE))
		if (print_status(m, philo_name, "has taken a fork", NOT_EAT))
			return (ERROR);
	return (OK);
}

int	philo_eats(t_main *m, int philo_name, int left, int right)
{	
	if (take_forks(m, philo_name, left, right))
		return (ERROR);
	if (pthread_mutex_lock(&m->mutex_ctrl[ALIVE]))
		return (critical_exit(m));
	if (add_meal(m))
		return (ERROR);
	if (smb_died(m) == TRUE || all_full(m) == TRUE)
		return (unlock_forks(m, left, right));
	else
		if (print_status(m, philo_name, "\033[33mis eating\033[0m", EAT))
			return (ERROR);
	if (add_global_meal(m, philo_name))
		return (ERROR);
	if (pthread_mutex_unlock(&m->mutex_ctrl[ALIVE]))
		return (critical_exit(m));
	if (usleep(m->info.time_to_eat))
		return (critical_exit(m));
	if (pthread_mutex_unlock(&m->mutex_fork[right]))
		return (critical_exit(m));
	if (pthread_mutex_unlock(&m->mutex_fork[left]))
		return (critical_exit(m));
	return (OK);
}