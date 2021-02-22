/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:32:25 by rcamilo-          #+#    #+#             */
/*   Updated: 2020/02/18 17:49:49 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t d_size;
	size_t s_size;

	d_size = ft_strlen(dst);
	s_size = ft_strlen(src);
	if (dstsize == 0)
		return (s_size);
	i = 0;
	if (dstsize > d_size)
		while (src[i] && i < dstsize - d_size - 1)
		{
			dst[d_size + i] = src[i];
			i++;
		}
	if (d_size + i <= dstsize)
		dst[d_size + i] = '\0';
	return (dstsize < d_size) ? (s_size + dstsize) : (d_size + s_size);
}
