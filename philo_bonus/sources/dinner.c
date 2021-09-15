/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:53:12 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 19:56:42 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_main *m, int philo_name)
{
	if (sem_wait(m->table))
		return (kill(0, SIGTERM));
	if (sem_wait(m->forks))
		return (kill(0, SIGTERM));
	
	if (sem_wait(m->print))
			return (kill(0, SIGTERM));
	if (print_status(m, philo_name, "has taken a fork", NOT_EAT))
		return (ERROR);
	if (sem_post(m->print))
		return (kill(0, SIGTERM));
	if (sem_wait(m->forks))
		return (kill(0, SIGTERM));
	
	if (sem_wait(m->print))
			return (kill(0, SIGTERM));
	if (print_status(m, philo_name, "has taken a fork", NOT_EAT))
		return (ERROR);
	if (sem_post(m->print))
		return (kill(0, SIGTERM));
	if (sem_post(m->table))
		return (kill(0, SIGTERM));
	return (OK);
}

int	philo_eats(t_main *m, int philo_name)
{
	if (take_forks(m, philo_name))
		return (ERROR);
	if (sem_wait(m->print))
			return (kill(0, SIGTERM));
	if (print_status(m, philo_name, "\033[33mis eating\033[0m", EAT))
		return (ERROR);
	m->curr_num_of_meals++;
	if (m->info.num_of_meals != -1 && m->curr_num_of_meals >= m->info.num_of_meals)
	{
		if (sem_post(m->print))
			return (kill(0, SIGTERM));
		if (sem_post(m->forks))
			return (kill(0, SIGTERM));
		if (sem_post(m->forks))
			return (kill(0, SIGTERM));
		if (pthread_join(m->pathologist, NULL))
			return (kill(0, SIGTERM));
		return (FULL);
	}
	if (sem_post(m->print))
		return (kill(0, SIGTERM));	
	if (usleep(m->info.time_to_eat))
		return (kill(0, SIGTERM));
	if (sem_post(m->forks))
		return (kill(0, SIGTERM));
	if (sem_post(m->forks))
		return (kill(0, SIGTERM));
	return (OK);
}