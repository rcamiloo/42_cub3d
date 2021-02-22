/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 17:28:06 by rcamilo-          #+#    #+#             */
/*   Updated: 2020/02/08 18:05:49 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*dest;

	dest = NULL;
	size = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * size + 1);
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s1, size);
	dest[size] = '\0';
	return (dest);
}
