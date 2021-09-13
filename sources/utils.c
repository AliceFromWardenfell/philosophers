/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 03:58:34 by alisa             #+#    #+#             */
/*   Updated: 2021/09/13 12:42:53 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	curr_timestamp(t_main *m, int philo_name)
{
	struct timeval	curr_time;
	long			birth_time_s;
	long			birth_time_us;
	long			timestamp;
	int				diff;

	birth_time_s = m->philo[philo_name - 1].birth_time.tv_sec;
	birth_time_us = m->philo[philo_name - 1].birth_time.tv_usec;
	if (gettimeofday(&curr_time, NULL))
		return (-1);
	diff = curr_time.tv_usec - birth_time_us;
	timestamp = (curr_time.tv_sec - birth_time_s) * 1000000 + diff;
	return (timestamp / 1000);
}

int	print_status(t_main *m, int philo_name, char *status, int flag) //mb move
{
	long	timestamp;
	// printf("%d. old_last_meal = %ld\n", philo_name, m->philo[philo_name - 1].last_meal_time);
	timestamp = curr_timestamp(m, philo_name);
	if (timestamp == -1)
			return (critical_exit(m));
	if (flag == EAT)
		m->philo[philo_name - 1].last_meal_time = timestamp;
	printf("%05ld \033[1m%4d\033[0m %s\n", timestamp, philo_name, status);
	
	return (0);
}

int	unlock_all_philo(t_main *m, int expected_amount_of_meals)
{
	int	i;

	i = -1;
	while (TRUE)
	{
		// printf("%d %d\n", m->info.num_of_finished_meals, expected_amount_of_meals);
		if (m->info.num_of_finished_meals == expected_amount_of_meals)
		{
			while (++i < m->info.num_of_philos)
			{
				if (pthread_mutex_unlock(&m->mutex_philo[i]))
					return (critical_exit(m));
				// printf("last_unlock: %d.\n", i + 1);
			}
			break ;
		}
		if (usleep(1000))
			return (critical_exit(m));
	}
	return (2);
}

int	all_full(t_main *m)
{
	if (m->info.num_of_full_philos == m->info.num_of_philos)
		return (TRUE);
	return (FALSE);
}

int	smb_died(t_main *m)
{
	if (m->info.somebody_died)
		return (TRUE);
	return (FALSE);
}
