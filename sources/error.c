/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 07:16:13 by alisa             #+#    #+#             */
/*   Updated: 2021/09/12 06:32:55 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(t_main *m)
{
	if (m->mutex_fork)
		free(m->mutex_fork);
	if (m->mutex_ctrl)
		free(m->mutex_ctrl);
	if (m->mutex_philo)
		free(m->mutex_philo);
	if (m->thread)
		free(m->thread);
	if (m->mutex_philo)
		free(m->mutex_philo);
	if (m->pathologist)
		free(m->pathologist);
	printf("Error!\n");
	return (1);
}
