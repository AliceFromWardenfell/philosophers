/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:16:46 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 15:37:29 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_main *m)
{
	if (m->pid)
		free(m->pid);
	sem_unlink("forks");
	sem_unlink("alive");
	sem_unlink("print");
	sem_unlink("kill");
	sem_unlink("table");
}

int	print_error(char *str)
{
	printf("\033[31mERROR:\033[0m %s\n", str);
	return (ERROR);
}
