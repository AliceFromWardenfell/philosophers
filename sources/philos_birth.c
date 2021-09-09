/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_birth.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 07:21:16 by alisa             #+#    #+#             */
/*   Updated: 2021/09/09 05:32:17 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_main *m, int philo_name, int left, int right)
{
	pthread_mutex_lock(&m->mutex_ctrl[TABLE]);
	pthread_mutex_lock(&m->mutex_fork[left]);
	// printf("%d has taken %d fork\n", philo_name, left);
	// usleep(1000000);
	pthread_mutex_lock(&m->mutex_fork[right]);
	// printf("%d has taken %d fork\n", philo_name, right);
	printf("%d starts eating.\n", philo_name);
	usleep(1000000);
	// printf("%d has put %d fork\n", philo_name, left);
	pthread_mutex_unlock(&m->mutex_fork[left]);
	// printf("%d has put %d fork\n", philo_name, right);
	pthread_mutex_unlock(&m->mutex_fork[right]);
	pthread_mutex_unlock(&m->mutex_ctrl[TABLE]);
}

void	philo_sleeps(void)
{
	usleep(500000);
}

void	*philo_life(void *arg)
{
	t_main	*m;
	int		philo_name;
	int		left;
	int		right;

	m = (t_main *)arg;
	pthread_mutex_lock(&m->mutex_ctrl[NAME]);
	philo_name = m->info.free_name++;
	pthread_mutex_unlock(&m->mutex_ctrl[NAME]);
	left = philo_name % m->info.num_of_philos;
	right = philo_name - 1;
	while (TRUE)
	{
		philo_eats(m, philo_name, left, right);
		philo_sleeps();
	}
	return (NULL);
}

void	philos_birth(t_main *m)
{
	int		i;

	i = -1;
	while (++i < m->info.num_of_philos)
		pthread_create(&m->thread[i], NULL, &philo_life, (void *)m);
}
