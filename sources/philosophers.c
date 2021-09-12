/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 07:21:16 by alisa             #+#    #+#             */
/*   Updated: 2021/09/12 11:19:40 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	unlock_forks(t_main *m, int left, int right)
{
	if (pthread_mutex_unlock(&m->mutex_ctrl[ALIVE]))
		return (ERROR);
	if (pthread_mutex_unlock(&m->mutex_fork[right]))
		return (ERROR);
	if (pthread_mutex_unlock(&m->mutex_fork[left]))
		return (ERROR);
	return (2);
}

static int	philo_eats(t_main *m, int philo_name, int left, int right)
{	
	printf("%d waiting for permision to eat\n", philo_name);
	if (pthread_mutex_lock(&m->mutex_philo[philo_name - 1]))
		return (ERROR);
	if (pthread_mutex_lock(&m->mutex_fork[right]))
		return (ERROR);
	// printf("%d has taken %d fork\n", philo_name, right);
	if (pthread_mutex_lock(&m->mutex_fork[left]))
		return (ERROR);
	// printf("%d has taken %d fork\n", philo_name, left);
	if (pthread_mutex_lock(&m->mutex_ctrl[ALIVE]))
		return (ERROR);
	if (pthread_mutex_lock(&m->mutex_ctrl[MEAL]))
		return (ERROR);
	// printf("adding 1 to %d finished_meals\n", m->info.num_of_finished_meals);
	m->info.num_of_finished_meals++;
	m->philo[philo_name - 1].curr_num_of_meals++;
	if (pthread_mutex_unlock(&m->mutex_ctrl[MEAL]))
		return (ERROR);
	if (smb_died(m) == TRUE)
		return (unlock_forks(m, left, right));
	else
		if (print_status(m, philo_name, "\033[33mis eating\033[0m"))
			return (ERROR);
	if (pthread_mutex_unlock(&m->mutex_ctrl[ALIVE]))
		return (ERROR);
	printf("%d. last_meal = %ld\n", philo_name, m->philo[philo_name - 1].last_meal_time);
	if (usleep(m->info.time_to_eat))
		return (ERROR);
	// printf("%d has put %d fork\n", philo_name, right);
	if (pthread_mutex_unlock(&m->mutex_fork[right]))
		return (ERROR);
	// printf("%d has put %d fork\n", philo_name, left);
	if (pthread_mutex_unlock(&m->mutex_fork[left]))
		return (ERROR);
	return (OK);
}

static int	philo_sleeps(t_main *m, int philo_name)
{
	usleep(philo_name);
	// if (print_status(m, philo_name, "is sleeping"))
	// 	return (ERROR);
	if (usleep(m->info.time_to_sleep))
		return (ERROR);
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
		return (NULL);
	philo_name = ++m->info.free_name;
	if (pthread_mutex_unlock(&m->mutex_ctrl[NAME]))
		return (NULL);
	left = philo_name % m->info.num_of_philos;
	right = philo_name - 1;
	if (gettimeofday(&m->philo[philo_name - 1].birth_time, NULL))
		return (NULL);
	while (TRUE)
	{
		if (philo_eats(m, philo_name, left, right))
		{
			printf("BYE from %d\n", philo_name);
			return (NULL); //free here if smthing was alloced
		}
		if (philo_sleeps(m, philo_name))
			return (NULL);
	}
	return (NULL);
}

int	philos_birth(t_main *m)
{
	int		i;

	i = -1;
	while (++i < m->info.num_of_philos)
		if (pthread_create(&m->thread[i], NULL, &philo_life, (void *)m))
			return (ERROR);
	return (OK);
}
