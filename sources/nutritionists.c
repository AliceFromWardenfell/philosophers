/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nutritionists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 10:42:29 by alisa             #+#    #+#             */
/*   Updated: 2021/09/12 13:39:06 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_nutrition(t_main *m, int i)
{
	if (pthread_mutex_lock(&m->mutex_ctrl[DIET]))
		return (ERROR);
	if (smb_died(m) == TRUE)
		return (2);
	if (m->philo[i].curr_num_of_meals >= m->info.num_of_meals && m->philo[i].is_full == FALSE)
	{
		m->philo[i].is_full = TRUE;
		m->info.num_of_full_philos++;
		if (all_full(m) == TRUE)
		{
			printf("BYE from nutritionist!\n");
			if (pthread_mutex_unlock(&m->mutex_ctrl[DIET]))
				return (ERROR);
			return (2);
		}
	}
	if (pthread_mutex_unlock(&m->mutex_ctrl[DIET]))
		return (ERROR);
	return (OK);
}

static void	*watch_for_diet(void *arg)
{
	t_main	*m;
	int		nutritionist_name;
	int		j;
	int		i;

	m = (t_main *)arg;
	if (pthread_mutex_lock(&m->mutex_ctrl[NAME]))
		return (NULL);
	nutritionist_name = ++m->info.free_name_n;
	if (pthread_mutex_unlock(&m->mutex_ctrl[NAME]))
		return (NULL);
	printf("HI from nutritionist %d!\n", nutritionist_name);
	while (TRUE)
	{
		i = nutritionist_name * 20 - 1;
		j = i + (20 + 1);
		if (m->info.num_of_philos < j)
			j = m->info.num_of_philos;
		while (++i < j)
			if (check_nutrition(m, i))
				return (NULL);
		if (usleep(1000))
			return (NULL);
	}
	return (NULL);
}

int	nutritionists_birth(t_main *m)
{
	int		i;

	i = -1;
	while (++i < m->info.num_of_pathologists)
	{
		if (pthread_create(&m->pathologist[i], NULL, &watch_for_diet, (void *)m))
			return (ERROR);
	}
	return (OK);
}
