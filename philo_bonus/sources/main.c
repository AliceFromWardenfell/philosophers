/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:03:46 by alisa             #+#    #+#             */
/*   Updated: 2021/09/14 13:16:25 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	initialization(t_main *m)
// {
// 	return (OK);
// }

int	main(int argc, char **argv)
{
	t_main m;

	if (parser(&m, argc, argv))
		return (ERROR);
	// if (initialization (&m))
	// 	return (ERROR);
	printf("OK\n");
	return (OK);
}