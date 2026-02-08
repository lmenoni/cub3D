/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:02:37 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/26 16:02:39 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*r;
	t_list	*t;

	if (!lst || !f || !del)
		return (NULL);
	r = (t_list *)ft_lstnew(f(lst->content));
	if (!r)
		return (NULL);
	t = r;
	lst = lst->next;
	while (lst)
	{
		t->next = ft_lstnew(f(lst->content));
		if (!t->next)
		{
			ft_lstclear(&r, del);
			del(lst->content);
			return (NULL);
		}
		t = t->next;
		lst = lst->next;
	}
	return (r);
}
