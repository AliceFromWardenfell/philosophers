/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 07:16:13 by alisa             #+#    #+#             */
/*   Updated: 2021/09/13 06:58:49 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_join(m->thread[i], NULL);
	i = -1;
	while (++i < m->info.num_of_pathologists)
	{
		pthread_join(m->pathologist[i], NULL);
		if (m->info.num_of_meals != -1)
			pthread_join(m->nutritionist[i], NULL);
	}
	pthread_join(m->waiter, NULL);
	return (OK);
}

int		destroy_mutexes(t_main *m)
{
	int	i;

	i = -1;
	while (++i < m->info.num_of_philos)
	{
		pthread_mutex_destroy(&m->mutex_fork[i]);
		pthread_mutex_destroy(&m->mutex_philo[i]);
	}
	i = -1;
	while (++i < 4)
		pthread_mutex_destroy(&m->mutex_ctrl[i]);
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
