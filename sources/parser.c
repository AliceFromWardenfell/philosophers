/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 03:53:59 by alisa             #+#    #+#             */
/*   Updated: 2021/09/13 06:15:39 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_if_num(char *argv)
{
	int		i;

	i = -1;
	while (argv[++i])
		if (argv[i] < '0' || argv[i] > '9')
			return (ERROR);
	return (OK);
}

static int	check_numbers(int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
		if (check_if_num(argv[i]))
			return (ERROR);
	return (OK);
}

static int	check_values(t_main *m) // handle MAX_INT
{
	if (m->info.num_of_philos < 1 || m->info.num_of_philos > 200)
		return (print_error("wrong number of philosophers"));
	if (m->info.time_to_die < 60 || m->info.time_to_die > 10000)
		return (print_error("wrong time to die"));
	if (m->info.time_to_eat < 60 || m->info.time_to_eat > 10000)
		return (print_error("wrong time to eat"));
	if (m->info.time_to_sleep < 60 || m->info.time_to_sleep > 10000)
		return (print_error("wrong time to sleep"));
	if (m->info.num_of_meals != -1
		&& (m->info.num_of_meals < 1 || m->info.num_of_meals > 1000))
		return (print_error("wrong number of meals"));
	m->info.time_to_eat *= 1000;
	m->info.time_to_sleep *= 1000;
	return (OK);
}

int	parser(t_main *m, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (print_error("wrong number of arguments"));
	if (check_numbers(argc, argv))
		return (print_error("wrong argument/arguments"));
	m->info.num_of_philos = ft_atoi(argv[1]);
	m->info.time_to_die = ft_atoi(argv[2]);
	m->info.time_to_eat = ft_atoi(argv[3]);
	m->info.time_to_sleep = ft_atoi(argv[4]);
	m->info.num_of_meals = -1;
	if (argc == 6)
		m->info.num_of_meals = ft_atoi(argv[5]);
	if (check_values(m))
		return (ERROR);
	return (OK);
}