/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 00:55:22 by alisa             #+#    #+#             */
/*   Updated: 2021/09/11 03:12:59 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	allow_odd_ones_to_eat(t_main *m, int expected_amount_of_meals)
{
	int		i;

	while (TRUE)
	{
		if (smb_died(m) == TRUE)
		{
			printf("BYE from waiter!\n");
			return (unlock_all_philo(m));
		}
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
	return (OK);
}

static int	allow_even_ones_to_eat(t_main *m)
{
	int		i;

	while (TRUE)
	{
		if (smb_died(m) == TRUE)
		{
			printf("BYE from waiter!\n");
			return (unlock_all_philo(m));
		}
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
	return (OK);
}

static int	allow_last_one_to_eat(t_main *m)
{
	while (TRUE)
	{
		if (smb_died(m) == TRUE)
		{
			printf("BYE from waiter!\n");
			return (unlock_all_philo(m));
		}
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
	return (OK);
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
		if (allow_odd_ones_to_eat(m, expected_amount_of_meals))
			return (NULL);
		if (allow_even_ones_to_eat(m))
			return (NULL);
		if (allow_last_one_to_eat(m))
			return (NULL);
	}
	return (NULL);
}

void	waiter_birth(t_main *m)
{
	pthread_create(&m->waiter, NULL, &waiter, (void *)m);
}
