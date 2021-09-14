/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 07:16:13 by alisa             #+#    #+#             */
/*   Updated: 2021/09/13 13:41:26 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	critical_exit(t_main *m)
{
	int				i;

	i = -1;
	while (++i < m->info.num_of_philos)
		pthread_detach(m->thread[i]);
	i = -1;
	while (++i < m->info.num_of_pathologists)
	{
		pthread_detach(m->pathologist[i]);
		if (m->info.num_of_meals != -1)
			pthread_detach(m->nutritionist[i]);
	}
	pthread_detach(m->waiter);
	return (ERROR);
}

void	*critical_exit_v(t_main *m)
{
	int				i;

	i = -1;
	while (++i < m->info.num_of_philos)
		pthread_detach(m->thread[i]);
	i = -1;
	while (++i < m->info.num_of_pathologists)
	{
		pthread_detach(m->pathologist[i]);
		if (m->info.num_of_meals != -1)
			pthread_detach(m->nutritionist[i]);
	}
	pthread_detach(m->waiter);
	return (NULL);
}

int	error_exit(t_main *m)
{
	mem_free(m);
	return (ERROR);
}

int	print_error(char *str)
{
	printf("\033[31mERROR:\033[0m %s\n", str);
	return (ERROR);
}
