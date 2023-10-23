/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:21:58 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/10/19 12:22:29 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_list	*sl_lstnew(int y, int x)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->x = x;
	node->y = y;
	node->next = NULL;
	return (node);
}

void	sl_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
	{
		new->next = *lst;
		*lst = new;
	}
}

t_list	*sl_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	sl_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	node = sl_lstlast(*lst);
	if (node)
		node->next = new;
	else
		sl_lstadd_front(lst, new);
}