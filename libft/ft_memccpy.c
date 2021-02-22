/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:58:07 by rcamilo-          #+#    #+#             */
/*   Updated: 2020/02/07 20:17:36 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*temp_d;
	unsigned char	*temp_s;

	temp_d = (unsigned char *)dst;
	temp_s = (unsigned char *)src;
	if ((!dst) && (!src) && n)
		return (dst);
	else
	{
		while (n > 0 && *temp_s != (unsigned char)c)
		{
			*temp_d++ = *temp_s++;
			n--;
		}
		if (n)
		{
			*temp_d++ = *temp_s++;
			return (temp_d);
		}
		return (NULL);
	}
	return (NULL);
}
