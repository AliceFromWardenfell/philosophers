/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathologist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:59:24 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 17:09:14 by alisa            ###   ########.fr       */
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
		// printf ("dc: print--\n");
		if (sem_wait(m->print))
			return (NULL);
		timestamp = curr_timestamp(m, m->name);
		if (timestamp == -1)
			return (NULL);
		// printf("%d. curr = %d, total = %d\n", m->name, m->curr_num_of_meals, m->info.num_of_meals);
		if (m->info.num_of_meals != -1 && m->curr_num_of_meals >= m->info.num_of_meals)
		{
			printf("bye from pathologist %d\n", m->name);
			if (sem_post(m->print))
				return (NULL);
			break ;
		}
		if (timestamp - m->philo[m->name -1].last_meal_time
			>= m->info.time_to_die)
		{
			if (print_status(m, m->name, "\033[31mdied\033[0m", NOT_EAT))
				return (NULL);
			if (sem_post(m->kill))
				return (NULL);
			return (NULL);
		}
		if (sem_post(m->print))
			return (NULL);
		// printf ("dc: print++\n");
		if (usleep(1000))
			return (NULL);
	}
	return (NULL);
}
