/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:56:26 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 20:07:27 by alisa            ###   ########.fr       */
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
		return (kill(0, SIGTERM));
	diff = curr_time.tv_usec - birth_time_us;
	timestamp = (curr_time.tv_sec - birth_time_s) * 1000000 + diff;
	return (timestamp / 1000);
}

int	print_status(t_main *m, int philo_name, char *status, int flag)
{
	long	timestamp;

	timestamp = curr_timestamp(m, philo_name);
	if (timestamp == -1)
		return (kill(0, SIGTERM));
	if (flag == EAT)
		m->philo[philo_name - 1].last_meal_time = timestamp;
	printf("%05ld \033[1m%4d\033[0m %s\n", timestamp, philo_name, status);
	return (OK);
}
