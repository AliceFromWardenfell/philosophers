/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:51:34 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 17:15:19 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*wait_for_order(void *arg)
{
	t_main *m;
	int		i;

	m = (t_main *)arg;
	if (sem_wait(m->kill))
		return (NULL);
	i = -1;
	while (++i < m->info.num_of_philos)
	{
		printf("killing %d...\n", i);
		kill(m->pid[i], SIGTERM);
	}
	return (NULL);
}

int	killer_birth(t_main *m)
{
	if (pthread_create(&m->killer, NULL, &wait_for_order, (void *)m))
		return (ERROR);
	return (OK);
}