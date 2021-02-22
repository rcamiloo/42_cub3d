/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:24:22 by rcamilo-          #+#    #+#             */
/*   Updated: 2020/02/14 22:09:21 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isspace(int c)
{
	if (c == '\n' || c == ' ' || c == '\v' || c == '\t'
			|| c == '\r' || c == '\f')
		return (1);
	else
		return (0);
}

static int	ft_overlimit(long n, int signal)
{
	if (n > INT_MAX)
	{
		if (signal == 1)
			return (1);
		else if (n - 1 > INT_MAX)
			return (-1);
	}
	return (0);
}

int			ft_atoi(const char *str)
{
	int		signal;
	long	result;

	signal = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		signal = (*str == '-') ? -1 : 1;
		str++;
	}
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			result = result * 10 + (*str - '0');
			str++;
			if (ft_overlimit(result, signal))
				return (ft_overlimit(result, signal) == 1 ? -1 : 0);
		}
		else
			return (signal * (int)result);
	}
	return (signal * (int)result);
}
