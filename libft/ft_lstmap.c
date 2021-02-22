/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 20:42:59 by rcamilo-          #+#    #+#             */
/*   Updated: 2020/02/14 21:05:11 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;

	if (!lst)
		return (NULL);
	if (!(result = ft_lstnew(f(lst->content))))
	{
		ft_lstclear(&result, del);
		return (NULL);
	}
	result->next = ft_lstmap(lst->next, f, del);
	return (result);
}
