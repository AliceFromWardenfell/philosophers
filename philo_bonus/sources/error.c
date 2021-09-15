/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:16:46 by alisa             #+#    #+#             */
/*   Updated: 2021/09/15 20:48:17 by alisa            ###   ########.fr       */
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

static void	prompt(void)
{
	printf("\n************************************** \033[1mHOW_TO_USE\033[0;39m\
 ************************************\n");
	printf(" ./philo '\033[36mnum_of_philos\033[0;39m' '\033[35mtime_to_die\033[0;39m'\
 '\033[33mtime_to_eat\033[0;39m' '\033[34mtime_to_sleep\033[0;39m'\
 ['\033[32mnum_of_meals\033[0;39m']  \n");
	printf("                            \
                                                           \n");
	printf("  \033[1m1\033[0;39m <= \033[36mnum_of_philos\033[0;39m <= \033[1m200\
                                                            \n");
	printf(" 60\033[0;39m <= \033[35mtime_to_die\033[0;39m   <= \033[1m10000\
                                                          \n");
	printf(" 60\033[0;39m <= \033[33mtime_to_eat\033[0;39m   <= \033[1m5000\
                                                           \n");
	printf(" 60\033[0;39m <= \033[34mtime_to_sleep\033[0;39m <= \033[1m5000\
                                                           \n");
	printf("  1\033[0;39m <= \033[32mnum_of_meals\033[0;39m  <= \033[1m1000\
\033[0;39m [optional]                                                \n");
	printf("*************************************************************\
*************************\n\n");
}

int	print_error(char *str)
{
	printf("\033[31mERROR:\033[0m %s\n", str);
	prompt();
	return (ERROR);
}
