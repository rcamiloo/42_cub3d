/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:56:28 by rcamilo-          #+#    #+#             */
/*   Updated: 2020/02/08 19:35:38 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size_s1;
	size_t	size_s2;
	char	*dest;

	size_s1 = 0;
	size_s2 = 0;
	if (s1)
		size_s1 = ft_strlen(s1);
	if (s2)
		size_s2 = ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (size_s1 + size_s2) + 1);
	if (dest == NULL)
		return (NULL);
	if (s1)
		ft_memcpy(dest, s1, size_s1);
	if (s2)
		ft_memcpy(dest + size_s1, s2, size_s2);
	dest[size_s1 + size_s2] = '\0';
	return (dest);
}
