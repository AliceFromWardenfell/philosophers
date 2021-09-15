/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:53:12 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 17:08:30 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_main *m, int philo_name)
{
	// if (check_if_still_alive(m, philo_name))
	// 	return (ERROR);
	if (sem_wait(m->table))
		return (print_error("sem_wait"));
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

	// if (check_if_still_alive(m, philo_name))
	// 	return (ERROR);
	if (sem_wait(m->forks))
		return (print_error("sem_wait"));
	
	if (sem_wait(m->print))
			return (print_error("sem_wait: print"));
	// printf ("e: print--\n");
	if (print_status(m, philo_name, "has taken a fork", NOT_EAT))
		return (ERROR);
	// printf(" %ld %d\n", m->philo[philo_name - 1].last_meal_time, m->info.time_to_die);
	if (sem_post(m->print))
		return (print_error("sem_wait: print"));
	if (sem_post(m->table))
		return (print_error("sem_wait"));
	return (OK);
}

int	philo_eats(t_main *m, int philo_name)
{
	// printf("philo %d in philo_eats\n", philo_name);
	// printf("philo %d still alive\n", philo_name);
	
	if (take_forks(m, philo_name))
		return (OK);

	// if (check_if_still_alive(m, philo_name))
	// 	return (ERROR);
	if (sem_wait(m->print))
			return (print_error("sem_wait: print"));
	if (print_status(m, philo_name, "\033[33mis eating\033[0m", EAT))
		return (ERROR);
	m->curr_num_of_meals++;
	if (m->info.num_of_meals != -1 && m->curr_num_of_meals >= m->info.num_of_meals)
	{
		if (sem_post(m->print))
			return (print_error("sem_wait: print"));
		if (sem_post(m->forks))
			return (print_error("sem_post"));
		if (sem_post(m->forks))
			return (print_error("sem_post"));
		if (pthread_join(m->pathologist, NULL))
			return (ERROR);
		printf("bye from %d\n", m->name);
		return (FULL);
	}
	// printf(" %ld %d\n", m->philo[philo_name - 1].last_meal_time, m->info.time_to_die);
	if (sem_post(m->print))
		return (print_error("sem_wait: print"));
	// printf ("e: print++\n");
	
	if (usleep(m->info.time_to_eat))
		return (ERROR);
	if (sem_post(m->forks))
		return (print_error("sem_post"));
	printf("%d has put a fork\n", philo_name);
	if (sem_post(m->forks))
		return (print_error("sem_post"));
	printf("%d has put a fork\n", philo_name);
	return (OK);
}