/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:48:07 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/10/20 15:22:11 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void search_exit(t_data *data, char **map, t_list **positions)
{
	int 	x;
	int 	y;
	t_list	*to_check;

	to_check = *positions;
	x = to_check->x;
	y = to_check->y;
	if (map[y][x] != '1')
	{
		if (map[y][x] == 'E')
			data->exit = 0;
		if (map[y][x] == 'C')
			data->coins -= 1;
		map[y][x] = '1';
		if (map[y][x - 1] != '1')
			sl_lstadd_back(positions, sl_lstnew(y, x - 1));
		if (map[y][x + 1] != '1')
			sl_lstadd_back(positions, sl_lstnew(y, x + 1));
		if (map[y - 1][x] != '1')
			sl_lstadd_back(positions, sl_lstnew(y - 1, x));
		if (map[y + 1][x] != '1')
			sl_lstadd_back(positions, sl_lstnew(y + 1, x));
	}
	*positions = to_check->next;
	free(to_check);
}

int	path_validator(t_data *data)
{
	t_list	**positions;
	char	**map;
	int 	i;

	positions = malloc(sizeof(t_list *));
	*positions = sl_lstnew(data->player_y, data->player_x);
	map = malloc(data->map_y * sizeof(char *));
	i = -1;
	while (data->map[++i] != NULL)
		map[i] = ft_strdup(data->map[i]);
	map[i] = NULL;
	search_exit(data, map, positions);
	while ((data->exit > 0 || data->coins >= 0) && *positions != NULL)
		search_exit(data, map, positions);
	i = 0;
	while (map[i] != NULL)
		free(map[i++]);
	free(map);
	free(positions);
	if (data->exit == 1 || data->coins > 0)
		return (0);
	return (1);
}
