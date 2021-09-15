/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 07:16:13 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 20:51:14 by alisa            ###   ########.fr       */
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

static void	prompt(void)
{
	printf("\n************************************** \033[1mHOW_TO_USE\033[0;39m\
 ************************************\n");
	printf(" ./philo '\033[36mnum_of_philos\033[0;39m' '\033[35mtime_to_die\033[0;39m'\
 '\033[33mtime_to_eat\033[0;39m' '\033[34mtime_to_sleep\033[0;39m'\
 ['\033[32mnum_of_meals\033[0;39m']  \n");
	printf("                            \
                                                           \n");
	printf("  \033[1m1\033[0;39m <= \033[36mnum_of_philos\033[0;39m <= \033[1m9999\
                                                           \n");
	printf(" 10\033[0;39m <= \033[35mtime_to_die\033[0;39m   <= \033[1m10000\
                                                          \n");
	printf("  1\033[0;39m <= \033[33mtime_to_eat\033[0;39m   <= \033[1m5000\
                                                           \n");
	printf("  1\033[0;39m <= \033[34mtime_to_sleep\033[0;39m <= \033[1m5000\
                                                           \n");
	printf("  1\033[0;39m <= \033[32mnum_of_meals\033[0;39m  <= \033[1m10000\
\033[0;39m [optional]                                               \n");
	printf("*************************************************************\
*************************\n\n");
}

int	print_error(char *str)
{
	printf("\033[31mERROR:\033[0m %s\n", str);
	prompt();
	return (ERROR);
}
