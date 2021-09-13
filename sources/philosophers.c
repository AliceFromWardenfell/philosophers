/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 07:21:16 by alisa             #+#    #+#             */
/*   Updated: 2021/09/13 12:24:19 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	unlock_forks(t_main *m, int left, int right)
{
	if (pthread_mutex_unlock(&m->mutex_ctrl[ALIVE]))
		return (critical_exit(m));
	if (pthread_mutex_unlock(&m->mutex_fork[right]))
		return (critical_exit(m));
	if (pthread_mutex_unlock(&m->mutex_fork[left]))
		return (critical_exit(m));
	return (2);
}

static int	philo_eats(t_main *m, int philo_name, int left, int right)
{	
	// printf("%d waiting for permision to eat\n", philo_name);
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
	if (pthread_mutex_lock(&m->mutex_ctrl[ALIVE]))
		return (critical_exit(m));
	if (pthread_mutex_lock(&m->mutex_ctrl[MEAL]))
		return (critical_exit(m));
	// printf("adding 1 to %d finished_meals\n", m->info.num_of_finished_meals);
	m->info.num_of_finished_meals++;
	if (pthread_mutex_unlock(&m->mutex_ctrl[MEAL]))
		return (critical_exit(m));
	if (smb_died(m) == TRUE || all_full(m) == TRUE)
		return (unlock_forks(m, left, right));
	else
		if (print_status(m, philo_name, "\033[33mis eating\033[0m", EAT))
			return (ERROR);
	if (pthread_mutex_lock(&m->mutex_ctrl[DIET]))
		return (critical_exit(m));
	m->philo[philo_name - 1].curr_num_of_meals++;
	if (pthread_mutex_unlock(&m->mutex_ctrl[DIET]))
		return (critical_exit(m));
	if (pthread_mutex_unlock(&m->mutex_ctrl[ALIVE]))
		return (critical_exit(m));
	// printf("%d. last_meal = %ld\n", philo_name, m->philo[philo_name - 1].last_meal_time);
	if (usleep(m->info.time_to_eat))
		return (critical_exit(m));
	// printf("%d has put %d fork\n", philo_name, right);
	if (pthread_mutex_unlock(&m->mutex_fork[right]))
		return (critical_exit(m));
	// printf("%d has put %d fork\n", philo_name, left);
	if (pthread_mutex_unlock(&m->mutex_fork[left]))
		return (critical_exit(m));
	return (OK);
}

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
		{
			// printf("E: BYE from %d\n", philo_name);
			return (NULL); //free here if smthing was alloced
		}
		if (philo_sleeps(m, philo_name))
		{
			// printf("S: BYE from %d\n", philo_name);
			return (NULL);
		}
		if (philo_thinks(m, philo_name))
		{
			// printf("T: BYE from %d\n", philo_name);
			return (NULL);
		}
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
