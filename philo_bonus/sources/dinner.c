/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:53:12 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 10:34:25 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eats(t_main *m, int philo_name)
{
	// printf("philo %d in philo_eats\n", philo_name);
	if (check_if_still_alive(m, philo_name))
		return (ERROR);
	// printf("philo %d still alive\n", philo_name);
	if (sem_wait(m->forks))
		return (print_error("sem_wait"));
	
	if (sem_wait(m->print))
			return (print_error("sem_wait: print"));
	// printf ("e: print--\n");
	if (print_status(m, philo_name, "has taken a fork", NOT_EAT))
		return (ERROR);
	if (sem_post(m->print))
		return (print_error("sem_wait: print"));
	// printf ("e: print++\n");
	
	if (sem_wait(m->forks))
		return (print_error("sem_wait"));
	
	if (sem_wait(m->print))
			return (print_error("sem_wait: print"));
	// printf ("e: print--\n");
	if (print_status(m, philo_name, "has taken a fork", NOT_EAT))
		return (ERROR);
	if (print_status(m, philo_name, "\033[33mis eating\033[0m", EAT))
		return (ERROR);
	if (sem_post(m->print))
		return (print_error("sem_wait: print"));
	// printf ("e: print++\n");
	
	if (usleep(m->info.time_to_eat))
		return (ERROR);
	if (sem_post(m->forks))
		return (print_error("sem_post"));
	if (sem_post(m->forks))
		return (print_error("sem_post"));
	return (OK);
}