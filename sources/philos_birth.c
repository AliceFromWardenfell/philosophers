/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_birth.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 07:21:16 by alisa             #+#    #+#             */
/*   Updated: 2021/09/11 03:18:49 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_eats(t_main *m, int philo_name, int left, int right)
{	
	printf("%d waiting for permision to eat\n", philo_name);
	pthread_mutex_lock(&m->mutex_philo[philo_name - 1]);
	printf("%d: check for deaths\n", philo_name);
	if (smb_died(m) == TRUE)
		return (TRUE);
	pthread_mutex_lock(&m->mutex_fork[right]);
	// printf("%d has taken %d fork\n", philo_name, right);
	pthread_mutex_lock(&m->mutex_fork[left]);
	// printf("%d has taken %d fork\n", philo_name, left);
	print_status(m, philo_name, "is eating");
	usleep(100000);
	pthread_mutex_lock(&m->mutex_ctrl[MEAL]);
	m->info.num_of_finished_meals++;
	pthread_mutex_unlock(&m->mutex_ctrl[MEAL]);
	// printf("%d has put %d fork\n", philo_name, right);
	pthread_mutex_unlock(&m->mutex_fork[right]);
	// printf("%d has put %d fork\n", philo_name, left);
	pthread_mutex_unlock(&m->mutex_fork[left]);
	return (OK);
}

static void	philo_sleeps(void)
{
	usleep(60000);
}

void	*philo_life(void *arg)
{
	t_main	*m;
	int		philo_name;
	int		left;
	int		right;

	m = (t_main *)arg;
	pthread_mutex_lock(&m->mutex_ctrl[NAME]);
	philo_name = ++m->info.free_name;
	pthread_mutex_unlock(&m->mutex_ctrl[NAME]);
	left = philo_name % m->info.num_of_philos;
	right = philo_name - 1;
	gettimeofday(&m->philo[philo_name - 1].birth_time, NULL);
	while (TRUE)
	{
		if (philo_eats(m, philo_name, left, right))
		{
			printf("BYE from %d\n", philo_name);
			return (NULL); //free here if smthing was alloced
		}
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
