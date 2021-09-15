/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathologist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:59:24 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 19:57:21 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*pathologist(void *arg)
{
	t_main 		*m;
	long		timestamp;

	m = (t_main *)arg;
	while (TRUE)
	{
		if (sem_wait(m->print))
			kill(0, SIGTERM);
		timestamp = curr_timestamp(m, m->name);
		if (timestamp == -1)
			kill(0, SIGTERM);
		if (m->info.num_of_meals != -1 && m->curr_num_of_meals >= m->info.num_of_meals)
		{
			if (sem_post(m->print))
				kill(0, SIGTERM);
			break ;
		}
		if (timestamp - m->philo[m->name -1].last_meal_time
			>= m->info.time_to_die)
		{
			if (print_status(m, m->name, "\033[31mdied\033[0m", NOT_EAT))
				return (NULL);
			if (sem_post(m->kill))
				kill(0, SIGTERM);
			return (NULL);
		}
		if (sem_post(m->print))
			kill(0, SIGTERM);
		if (usleep(1000))
			kill(0, SIGTERM);
	}
	return (NULL);
}
