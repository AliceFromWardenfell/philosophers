/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 15:01:32 by cvrone            #+#    #+#             */
/*   Updated: 2021/09/13 04:36:40 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long int	ft_atoi(const char *str)
{
	unsigned int	index;
	short int		sign;
	long int		rezult;

	rezult = 0;
	sign = 1;
	index = 0;
	while (str[index] == ' ' || str[index] == '\f' || str[index] == '\v'
		|| str[index] == '\r' || str[index] == '\n' || str[index] == '\t')
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while (str[index] > 47 && str[index] < 58)
	{
		rezult = rezult * 10 + str[index] - 48;
		index++;
	}
	return (sign * rezult);
}
