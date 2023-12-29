/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_import.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:09:22 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/29 14:11:42 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_temp_list	*add_node(char *content)
{
	t_temp_list	*node;

	node = (t_temp_list *)malloc(sizeof(t_list));
	node->line = ft_strtrim(content, "\n");
	if (!node->line || !node->line[0])
	{
		free(node->line);
		node->line = NULL;
	}
	node->next = NULL;
	free(content);
	return (node);
}

void	import_map(t_data *data, int fd)
{
	t_temp_list	*list;
	t_temp_list	*node;
	t_temp_list	*head;
	int			y;

	list = add_node(get_next_line(fd));
	head = list;
	data->map_y = 2;
	while (list->line)
	{
		node = add_node(get_next_line(fd));
		list->next = node;
		list = node;
		data->map_y++;
	}
	data->map = malloc(sizeof(char *) * data->map_y - 2);
	y = 0;
	while (head)
	{
		node = head;
		data->map[y++] = head->line;
		head = node->next;
		free(node);
	}
}
