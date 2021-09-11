/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 02:13:28 by alisa             #+#    #+#             */
/*   Updated: 2021/09/11 03:00:04 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watch_for_deaths(void *arg)
{
	t_main	*m;
	int		pathologist_name;
	int		j;
	int		i;

	m = (t_main *)arg;
	pthread_mutex_lock(&m->mutex_ctrl[NAME]);
	pathologist_name = ++m->info.free_name_;
	pthread_mutex_unlock(&m->mutex_ctrl[NAME]);
	printf("HI from pathologist %d!\n", pathologist_name);
	while (TRUE)
	{
		i = pathologist_name * 20 - 1;
		j = i + (20 + 1);
		if (m->info.num_of_philos < j)
			j = m->info.num_of_philos;
		while (++i < j)
		{
			usleep(3000000);
			m->info.somebody_died = TRUE;
			printf("BYE from pathologist %d!\n", pathologist_name);
			return (NULL);
		}
	}
	return (NULL);
}

void	pathologist_birth(t_main *m)
{
	int		i;

	i = -1;
	while (++i < m->info.num_of_pathologists)
	{
		pthread_create(&m->pathologist[i], NULL, &watch_for_deaths, (void *)m);
	}
}

// void	nutritionist(t_main *m)
// {
	
// }

void	doctors(t_main *m)
{
	pathologist_birth(m);
	// nutritionist(m);
}
