/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathologist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 02:13:28 by alisa             #+#    #+#             */
/*   Updated: 2021/09/12 07:53:27 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	death_check(t_main *m, int philo_name)
{
	long	timestamp;

	timestamp = curr_timestamp(m, philo_name);
	if (timestamp == -1)
		return (ERROR);
	if (timestamp - m->philo[philo_name - 1].last_meal_time
		>= m->info.time_to_die)
	{
		printf("%d. last_meal = %ld\n", philo_name, m->philo[philo_name - 1].last_meal_time);
		m->info.somebody_died = TRUE;
		if (pthread_mutex_lock(&m->mutex_ctrl[ALIVE]))
			return (ERROR);
		if (print_status(m, philo_name, "died"))
			return (ERROR);
		if (pthread_mutex_unlock(&m->mutex_ctrl[ALIVE]))
			return (ERROR);
		return (2);
	}
	return (0);
}

void	*watch_for_deaths(void *arg)
{
	t_main	*m;
	int		pathologist_name;
	int		j;
	int		i;

	m = (t_main *)arg;
	if (pthread_mutex_lock(&m->mutex_ctrl[NAME]))
		return (NULL);
	pathologist_name = ++m->info.free_name_;
	if (pthread_mutex_unlock(&m->mutex_ctrl[NAME]))
		return (NULL);
	printf("HI from pathologist %d!\n", pathologist_name);
	while (TRUE)
	{
		i = pathologist_name * 20 - 1;
		j = i + (20 + 1);
		if (m->info.num_of_philos < j)
			j = m->info.num_of_philos;
		while (++i < j)
			if (death_check(m, i + 1))
				return (NULL);
		if (usleep(1000))
			return (NULL);
	}
	return (NULL);
}

int	pathologist_birth(t_main *m)
{
	int		i;

	i = -1;
	while (++i < m->info.num_of_pathologists)
	{
		if (pthread_create(&m->pathologist[i], NULL, &watch_for_deaths, (void *)m))
			return (ERROR);
	}
	return (OK);
}

// void	nutritionist(t_main *m)
// {
	
// }

// void	doctors(t_main *m)
// {
// 	pathologist_birth(m);
// 	// nutritionist(m);
// }
