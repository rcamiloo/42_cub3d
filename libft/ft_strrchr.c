/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 14:59:55 by rcamilo-          #+#    #+#             */
/*   Updated: 2020/01/24 19:30:52 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = NULL;
	if ((char)c == '\0')
	{
		s = s + ft_strlen(s);
		return (char *)s;
	}
	while (*s)
	{
		if (*s == (char)c)
			last = (char*)s;
		s++;
	}
	return (last);
}
