/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <rcamilo-@student.42sp.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:49:08 by rcamilo-          #+#    #+#             */
/*   Updated: 2021/03/07 12:58:18 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_sanitize(char const *s1, char const *set)
{
	int		size_s;
	int		size_new;
	int		i;
	char	*new;

	size_s = ft_strlen(s1);
	size_new = 0;
	i = 0;
	while (s1[i])
		if(!ft_strchr(set, s1[i++]))
			size_new++;
	if (!(new = (char *)malloc(sizeof(char) * (size_new + 1))))
		return (NULL);
	ft_memset(new, '\0', size_new + 1);
	size_s--;
	size_new--;
	while (size_s >= 0)
	{
		if (!(ft_strchr(set, s1[size_s])))
			new[size_new--] = s1[size_s];
		size_s--;
	}
	return (new);
}
