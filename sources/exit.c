/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 07:16:13 by alisa             #+#    #+#             */
/*   Updated: 2021/09/13 13:29:12 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	critical_exit(t_main *m)
{
	int				i;

	i = -1;
	while (++i < m->info.num_of_philos)
		pthread_detach(m->thread[i]);
	i = -1;
	while (++i < m->info.num_of_pathologists)
	{
		pthread_detach(m->pathologist[i]);
		if (m->info.num_of_meals != -1)
			pthread_detach(m->nutritionist[i]);
	}
	pthread_detach(m->waiter);
	return (ERROR);
}

void	*critical_exit_v(t_main *m)
{
	int				i;

	i = -1;
	while (++i < m->info.num_of_philos)
		pthread_detach(m->thread[i]);
	i = -1;
	while (++i < m->info.num_of_pathologists)
	{
		pthread_detach(m->pathologist[i]);
		if (m->info.num_of_meals != -1)
			pthread_detach(m->nutritionist[i]);
	}
	pthread_detach(m->waiter);
	return (NULL);
}

int	error_exit(t_main *m)
{
	mem_free(m);
	return (ERROR);
}

int	print_error(char *str)
{
	printf("\033[31mERROR:\033[0m %s\n", str);
	return (ERROR);
}

int	wait_threads(t_main *m)
{
	int				i;

	i = -1;
	while (++i < m->info.num_of_philos)
		if (pthread_join(m->thread[i], NULL))
			return (ERROR);
	i = -1;
	while (++i < m->info.num_of_pathologists)
	{
		if (pthread_join(m->pathologist[i], NULL))
			return (ERROR);
		if (m->info.num_of_meals != -1)
			if (pthread_join(m->nutritionist[i], NULL))
				return (ERROR);
	}
	if (pthread_join(m->waiter, NULL))
		return (ERROR);
	return (OK);
}

int	destroy_mutexes(t_main *m)
{
	int	i;

	i = -1;
	while (++i < m->info.num_of_philos)
	{
		if (pthread_mutex_destroy(&m->mutex_fork[i]))
			return (ERROR);
		if (pthread_mutex_destroy(&m->mutex_philo[i]))
			return (ERROR);
	}
	i = -1;
	while (++i < 4)
		if (pthread_mutex_destroy(&m->mutex_ctrl[i]))
			return (ERROR);
	return (OK);
}

void	mem_free(t_main *m)
{
	if (m->mutex_fork)
		free(m->mutex_fork);
	if (m->mutex_ctrl)
		free(m->mutex_ctrl);
	if (m->mutex_philo)
		free(m->mutex_philo);
	if (m->thread)
		free(m->thread);
	if (m->philo)
		free(m->philo);
	if (m->pathologist)
		free(m->pathologist);
	if (m->nutritionist)
		free(m->nutritionist);
}
