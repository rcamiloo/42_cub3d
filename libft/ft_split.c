/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:46:07 by rcamilo-          #+#    #+#             */
/*   Updated: 2020/02/13 19:31:56 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_nb_tokens(char const *s, char c)
{
	size_t		nb_tokens;

	nb_tokens = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			nb_tokens++;
		while (*s != c && *s)
			s++;
	}
	return (nb_tokens);
}

size_t		ft_strclen(const char *s, char c)
{
	size_t size;

	size = 0;
	while (*s && (*s != c))
	{
		size++;
		s++;
	}
	return (size);
}

const char	*ft_worddup(char **array, const char *s, char c, size_t i)
{
	size_t	size_token;

	size_token = ft_strclen(s, c);
	if (!(array[i] = (char *)malloc(sizeof(char) * size_token + 1)))
		return (NULL);
	ft_memcpy(array[i], s, size_token);
	array[i][size_token] = '\0';
	return (s + size_token);
}

char		**ft_split(char const *s, char c)
{
	size_t	nb_tokens;
	size_t	i;
	char	**result;

	if (!s)
		return (NULL);
	nb_tokens = ft_nb_tokens(s, c);
	if (!(result = malloc((nb_tokens + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (i <= nb_tokens && *s)
	{
		while (*s == c)
			s++;
		if (*s)
			s = ft_worddup(result, s, c, i);
		i++;
	}
	result[nb_tokens] = NULL;
	return (result);
}
