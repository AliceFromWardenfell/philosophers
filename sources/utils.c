/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 03:58:34 by alisa             #+#    #+#             */
/*   Updated: 2021/09/11 03:36:53 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	curr_timestamp(t_main *m, int philo_name) //mb static
{
	struct timeval	curr_time;
	long			birth_time_s;
	long			birth_time_us;
	long			timestamp;
	int				diff;

	birth_time_s = m->philo[philo_name - 1].birth_time.tv_sec;
	birth_time_us = m->philo[philo_name - 1].birth_time.tv_usec;
	gettimeofday(&curr_time, NULL);
	diff = curr_time.tv_usec - birth_time_us;
	timestamp = (curr_time.tv_sec - birth_time_s) * 1000000 + diff;
	return (timestamp / 1000);
}

void	print_status(t_main *m, int philo_name, char *status) //mb move
{
	m->philo[philo_name - 1].last_meal_time = curr_timestamp(m, philo_name);
	printf("%05ld %d %s\n", m->philo[philo_name - 1].last_meal_time, philo_name, status);
}

int	unlock_all_philo(t_main *m, int expected_amount_of_meals)
{
	int	i;

	i = -1;
	while (TRUE)
	{
		if (m->info.num_of_finished_meals == expected_amount_of_meals)
		{
			while (++i < m->info.num_of_philos)
				pthread_mutex_unlock(&m->mutex_philo[i]);
			break ;
		}
		usleep(1000);
	}
	return (1);
}

int	smb_died(t_main *m)
{
	if (m->info.somebody_died)
		return (TRUE);
	return (FALSE);
}
