/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 02:41:07 by alisa             #+#    #+#             */
/*   Updated: 2021/09/04 18:59:58 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_yourself(int philo_name, int num_of_philos, pthread_mutex_t *locks)
{
	pthread_mutex_lock(&locks[philo_name - 1]);
	pthread_mutex_lock(&locks[philo_name - 1 + num_of_philos]);
	printf("%d locked himself (%d) (%d)\n", philo_name, philo_name - 1, philo_name - 1 + num_of_philos);
}

void	unlock_neighbours(int philo_name, int num_of_philos, pthread_mutex_t *locks)
{
	if (philo_name == 1)
	{
		pthread_mutex_unlock(&locks[num_of_philos - 1]);
		printf("%d unlocked %d's left lock (%d)\n", philo_name, num_of_philos, num_of_philos - 1);
	}
	else
	{
		pthread_mutex_unlock(&locks[philo_name - 2]);
		printf("%d unlocked %d's left lock (%d)\n", philo_name, philo_name - 1, philo_name - 2);
	}
	if (philo_name == num_of_philos)
	{
		pthread_mutex_unlock(&locks[num_of_philos]);
		printf("%d unlocked 1's right lock (%d)\n", philo_name, num_of_philos);
	}
	else
	{
		pthread_mutex_unlock(&locks[philo_name + num_of_philos]);
		printf("%d unlocked %d's right lock (%d)\n", philo_name, philo_name + 1, philo_name + num_of_philos);
	}
}

void	philo_eats(int philo_name, int num_of_philos, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(&mutex[philo_name]);
	pthread_mutex_lock(&mutex[philo_name % num_of_philos + 1]);
	printf("%d starts eating\n", philo_name);
	usleep(1000000);
	// printf("%d ends eating\n", philo_name);
	pthread_mutex_unlock(&mutex[philo_name]);
	pthread_mutex_unlock(&mutex[philo_name % num_of_philos + 1]);
}

void	philo_sleeps(void)
{
	// printf("%d starts sleeping\n", philo_name);
	usleep(1);
	// printf("%d ends sleeping\n", philo_name);
}

void	*philo_life(void *arg)
{
	t_main	*m;
	int		philo_name;

	m = (t_main *)arg;
	pthread_mutex_lock(&m->mutex[NAME]);
	philo_name = m->next_philo_name++;
	pthread_mutex_unlock(&m->mutex[NAME]);
	while (1)
	{
		lock_yourself(philo_name, m->num_of_philos, m->locks);
		philo_eats(philo_name, m->num_of_philos, m->mutex);
		unlock_neighbours(philo_name, m->num_of_philos, m->locks);
		philo_sleeps();
		// printf("%d starts thinking\n", philo_name);
	}
	return (NULL);
}

void	init(t_main *m)
{
	m->mutex = malloc((TH_NUM + 1) * sizeof(*m->mutex));
	m->locks = malloc(TH_NUM * 2 * sizeof(*m->locks));
	m->x = 0;
	m->next_philo_name = 1;
}

int	main(void)
{
	int			i;
	pthread_t	t1[TH_NUM];
	t_main		m;

	init(&m);
	m.num_of_philos = TH_NUM;
	i = -1;
	while (++i < TH_NUM)
		pthread_mutex_init(&m.mutex[i], NULL);
	i = -1;
	while (++i < TH_NUM * 2)
		pthread_mutex_init(&m.locks[i], NULL);
	i = -1;
	while (++i < TH_NUM)
	{
		pthread_create(&t1[i], NULL, &philo_life, (void *)&m);
	}
	i = -1;
	while (++i < TH_NUM)
		pthread_join(t1[i], NULL);
	return (0);
}
