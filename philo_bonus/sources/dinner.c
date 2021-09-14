/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:53:12 by alisa             #+#    #+#             */
/*   Updated: 2021/09/14 19:20:32 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eats(t_main *m, int philo_name)
{
	if (sem_wait(m->table))
			return (print_error("sem_wait: table"));
	if (sem_wait(m->forks))
		return (print_error("sem_wait"));
	if (print_status(m, philo_name, "has taken a fork", NOT_EAT))
		return (ERROR);
	if (sem_wait(m->forks))
		return (print_error("sem_wait"));
	if (print_status(m, philo_name, "has taken a fork", NOT_EAT))
		return (ERROR);
	if (sem_post(m->table))
		return (print_error("sem_wait: table"));
	if (print_status(m, philo_name, "\033[33mis eating\033[0m", EAT))
		return (ERROR);
	if (usleep(m->info.time_to_eat))
		return (ERROR);
	if (sem_post(m->forks))
		return (print_error("sem_post"));
	if (sem_post(m->forks))
		return (print_error("sem_post"));
	return (OK);
}