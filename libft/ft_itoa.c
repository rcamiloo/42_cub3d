/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 14:19:09 by rcamilo-          #+#    #+#             */
/*   Updated: 2020/02/14 21:39:57 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int		len;
	long	new;

	if (n == 0)
		return (1);
	len = 0;
	new = n;
	if (new < 0)
	{
		len++;
		new = -new;
	}
	while (new)
	{
		len++;
		new = new / 10;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int		len;
	char	*string;
	int		isnegative;
	long	i;
	long	new;

	len = ft_intlen(n);
	isnegative = (n < 0) ? 1 : 0;
	new = n;
	new = (n < 0) ? -new : new;
	if (!(string = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (i < len - isnegative)
	{
		string[i] = new % 10 + '0';
		new = new / 10;
		i++;
	}
	string[len - 1] = (isnegative == 1) ? '-' : string[len - 1];
	string[len] = '\0';
	ft_revstr(string);
	return (string);
}
