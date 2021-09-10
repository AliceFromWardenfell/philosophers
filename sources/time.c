/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 03:58:34 by alisa             #+#    #+#             */
/*   Updated: 2021/09/10 22:28:44 by alisa            ###   ########.fr       */
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
	// printf("%ld %ld\n", birth_time_s, birth_time_us);
	gettimeofday(&curr_time, NULL);
	// printf("%ld %ld\n", curr_time.tv_sec, curr_time.tv_usec);
	diff = curr_time.tv_usec - birth_time_us;
	// printf("diff: %d\n", diff);
	timestamp = (curr_time.tv_sec - birth_time_s) * 1000000 + diff;
	return (timestamp / 1000);
}
