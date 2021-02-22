/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 16:00:05 by rcamilo-          #+#    #+#             */
/*   Updated: 2020/02/20 15:20:31 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_revstr(char *s)
{
	size_t	size;
	size_t	i;
	char	temp;

	size = ft_strlen(s);
	i = 0;
	while (i < size / 2)
	{
		temp = s[i];
		s[i] = s[size - 1 - i];
		s[size - 1 - i] = temp;
		i++;
	}
}
