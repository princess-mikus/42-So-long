/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:58:40 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/13 14:16:38 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_valid_symbols(t_data *data, int x, int y)
{
	if (data->map[y][x] != '1' && \
		data->map[y][x] != '0' && \
		data->map[y][x] != 'C' && \
		data->map[y][x] != 'E' && \
		data->map[y][x] != 'P')
	{
		ft_printf("So Long: Error, not valid symbol on map\n");
		free_array(data->map);
		exit (2);
	}
}

int	duplicate_validator(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == 'P')
			{
				data->players++;
				data->player_x = x;
				data->player_y = y;
			}
			if (data->map[y][x] == 'E')
				data->exit++;
			if (data->map[y][x] == 'C')
				data->coins++;
		}
	}
	if (data->players != 1 || data->exit != 1 || data->coins < 0)
		return (0);
	return (1);
}

int	wall_validator(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y][x] == '1')
		x++;
	if (map[y][x])
		return (0);
	x--;
	while (map[y + 1])
	{
		if (map[y][0] != '1' || map[y][x] != '1')
			return (0);
		y++;
	}
	while (map[y][x] == '1')
		x++;
	if (map[y][x] || x != (int)ft_strlen(map[0]))
		return (0);
	return (1);
}

int	map_validator(t_data *data)
{
	data->exit = 0;
	data->coins = 0;
	if (!wall_validator(data->map))
	{
		ft_printf \
		("so_long: Error: Map not square or not surrounded by walls\n");
		return (0);
	}
	if (!duplicate_validator(data))
	{
		ft_printf("so_long: Error: Duplicate symbols, or not enough coins\n");
		return (0);
	}
	if (!path_validator(data))
	{
		ft_printf("so_long: Error: Map not playable, \
		player can't reach door and/or all coins\n");
		return (0);
	}
	return (1);
}
