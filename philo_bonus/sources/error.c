/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:16:46 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 20:08:35 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_main *m)
{
	if (m->pid)
		free(m->pid);
	if (m->philo)
		free(m->philo);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("kill");
	sem_unlink("table");
}

int	print_error(char *str)
{
	printf("\033[31mERROR:\033[0m %s\n", str);
	return (ERROR);
}
