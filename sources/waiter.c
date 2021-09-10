/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 00:55:22 by alisa             #+#    #+#             */
/*   Updated: 2021/09/10 03:54:10 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	allow_odd_ones_to_eat(t_main *m, int expected_amount_of_meals)
{
	int		i;

	while (TRUE)
	{
		if (m->info.num_of_finished_meals == expected_amount_of_meals)
		{
			printf("the odd ones...\n");
			i = 0;
			while (i < m->info.num_of_philos - 1)
			{
				pthread_mutex_unlock(&m->mutex_philo[i]);
				i += 2;
			}
			m->info.num_of_finished_meals = 0;
			break ;
		}
		usleep(10000);
	}
}

static void	allow_even_ones_to_eat(t_main *m)
{
	int		i;

	while (TRUE)
	{
		if (m->info.num_of_finished_meals == m->info.num_of_philos / 2)
		{
			printf("the even ones...\n");
			i = 1;
			while (i <= m->info.num_of_philos - 1)
			{
				pthread_mutex_unlock(&m->mutex_philo[i]);
				i += 2;
			}
			m->info.num_of_finished_meals = 0;
			break ;
		}
		usleep(10000);
	}
}

static void	allow_last_one_to_eat(t_main *m)
{
	while (TRUE)
	{
		if (m->info.num_of_philos % 2 == 0)
		{
			m->info.num_of_finished_meals = 0;
			break ;
		}
		if (m->info.num_of_finished_meals == m->info.num_of_philos / 2)
		{
			printf("the last one...\n");
			pthread_mutex_unlock(&m->mutex_philo[m->info.num_of_philos - 1]);
			m->info.num_of_finished_meals = 0;
			break ;
		}
		usleep(10000);
	}
}

static void	*waiter(void *arg)
{
	t_main	*m;
	int		expected_amount_of_meals;

	m = (t_main *)arg;
	if (m->info.num_of_philos % 2 == 0)
		expected_amount_of_meals = m->info.num_of_philos / 2;
	else
		expected_amount_of_meals = 1;
	while (TRUE)
	{
		allow_odd_ones_to_eat(m, expected_amount_of_meals);
		allow_even_ones_to_eat(m);
		allow_last_one_to_eat(m);
	}
	return (NULL);
}

void	waiter_birth(t_main *m)
{
	pthread_create(&m->waiter, NULL, &waiter, (void *)m);
}
