/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 23:42:33 by rcamilo-          #+#    #+#             */
/*   Updated: 2020/01/25 00:49:39 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	else
		while (*s1 && n > 1)
		{
			if (*s1 == *s2)
			{
				s1++;
				s2++;
			}
			else
			{
				return ((unsigned char)*s1 - (unsigned char)*s2);
			}
			n--;
		}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
