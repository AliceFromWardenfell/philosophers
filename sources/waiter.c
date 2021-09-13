/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 00:55:22 by alisa             #+#    #+#             */
/*   Updated: 2021/09/13 13:32:59 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	allow_odd_ones_to_eat(t_main *m, int expected_amount_of_meals)
{
	int		i;

	while (TRUE)
	{
		if (smb_died(m) == TRUE || all_full(m) == TRUE)
			return (unlock_all_philo(m, expected_amount_of_meals));
		if (m->info.num_of_finished_meals == expected_amount_of_meals)
		{
			m->info.num_of_finished_meals = 0;
			i = 0;
			while (i < m->info.num_of_philos - 1)
			{
				if (pthread_mutex_unlock(&m->mutex_philo[i]))
					return (critical_exit(m));
				if (smb_died(m) == TRUE || all_full(m) == TRUE)
					return (unlock_all_philo(m, i / 2 + 1));
				i += 2;
			}
			break ;
		}
		if (usleep(100))
			return (critical_exit(m));
	}
	return (OK);
}

static int	allow_even_ones_to_eat(t_main *m)
{
	int		i;

	while (TRUE)
	{
		if (smb_died(m) == TRUE || all_full(m) == TRUE)
			return (unlock_all_philo(m, m->info.num_of_philos / 2));
		if (m->info.num_of_finished_meals == m->info.num_of_philos / 2)
		{
			m->info.num_of_finished_meals = 0;
			i = 1;
			while (i <= m->info.num_of_philos - 1)
			{
				if (pthread_mutex_unlock(&m->mutex_philo[i]))
					return (critical_exit(m));
				if (smb_died(m) == TRUE || all_full(m) == TRUE)
					return (unlock_all_philo(m, (i + 1) / 2));
				i += 2;
			}
			break ;
		}
		if (usleep(100))
			return (critical_exit(m));
	}
	return (OK);
}

static int	allow_last_one_to_eat(t_main *m)
{
	while (TRUE)
	{
		if (smb_died(m) == TRUE || all_full(m) == TRUE)
			return (unlock_all_philo(m, m->info.num_of_philos / 2));
		if (m->info.num_of_finished_meals == m->info.num_of_philos / 2)
		{
			m->info.num_of_finished_meals = 0;
			if (pthread_mutex_unlock(&m->mutex_philo \
				[m->info.num_of_philos - 1]))
				return (critical_exit(m));
			if (smb_died(m) == TRUE || all_full(m) == TRUE)
				return (unlock_all_philo(m, 1));
			break ;
		}
		if (usleep(100))
			return (critical_exit(m));
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
	if (m->info.num_of_philos == 1)
	{
		if (pthread_mutex_unlock(&m->mutex_philo[0]))
			return (critical_exit_v(m));
		return (NULL);
	}
	while (TRUE)
	{
		if (allow_odd_ones_to_eat(m, expected_amount_of_meals))
			return (NULL);
		if (allow_even_ones_to_eat(m))
			return (NULL);
		if (m->info.num_of_philos % 2 == 1)
			if (allow_last_one_to_eat(m))
				return (NULL);
	}
	return (NULL);
}

int	waiter_birth(t_main *m)
{
	if (pthread_create(&m->waiter, NULL, &waiter, (void *)m))
		return (critical_exit(m));
	return (OK);
}
