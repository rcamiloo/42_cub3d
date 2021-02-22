/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:58:07 by rcamilo-          #+#    #+#             */
/*   Updated: 2020/02/07 15:03:24 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*temp_d;
	unsigned char	*temp_s;

	temp_d = (unsigned char *)dst;
	temp_s = (unsigned char *)src;
	if ((!dst) && (!src) && n)
		return (dst);
	else
		while (n--)
			*temp_d++ = *temp_s++;
	return (dst);
}
