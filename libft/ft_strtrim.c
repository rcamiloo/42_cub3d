/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <rcamilo-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:44:50 by rcamilo-          #+#    #+#             */
/*   Updated: 2021/02/25 18:48:52 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		size;
	const char	*inf_limit;
	const char	*sup_limit;
	char		*result;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1);
	inf_limit = s1;
	sup_limit = s1 + size - 1;
	while (ft_strchr(set, *inf_limit) && inf_limit < sup_limit)
		inf_limit++;
	while (ft_strchr(set, *sup_limit) && sup_limit > inf_limit)
		sup_limit--;
	size = (sup_limit == inf_limit) ? 0 : sup_limit - inf_limit + 1;
	result = (char *)malloc(sizeof(char) * size + 1);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, inf_limit, size);
	result[size] = '\0';
	return (result);
}
