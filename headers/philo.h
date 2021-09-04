/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 02:41:33 by alisa             #+#    #+#             */
/*   Updated: 2021/09/04 05:06:54 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

# define TH_NUM 7
# define NAME 0
# define OPEN 0
# define CLOSE 1

typedef struct s_main
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*locks;
	int				num_of_philos;
	int				next_philo_name;
	int				x;
}				t_main;

#endif