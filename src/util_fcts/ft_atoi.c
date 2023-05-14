/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadigh <kadigh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:15:30 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/05/08 17:26:00 by kadigh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

static int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

static int	valid_nbr(char *str)
{
	int	i;

	i = 0;
	if (*str == '-')
		return (0);
	else if (*str == '+')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_space(char *str)
{
	int	i;

	i = 0;
	while (((str[i] > 8 && str[i] < 14) || (str[i] == 32)) && str[i] != 0)
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	i = is_space(str);
	if (!valid_nbr(str + i))
		error("invalide arguments\n");
	while (str[i])
		result = result * 10 + (str[i++] - 48);
	return (result);
}
