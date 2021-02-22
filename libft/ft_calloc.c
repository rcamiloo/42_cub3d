/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:05:58 by rcamilo-          #+#    #+#             */
/*   Updated: 2020/02/08 18:19:54 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*dest;

	dest = (char *)malloc(sizeof(char) * count * size);
	if (dest == NULL)
		return (NULL);
	ft_memset(dest, '\0', count * size);
	return (dest);
}
