/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_modification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:14:46 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/11/29 14:35:14 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	river_checker(t_data *data, int x, int y)
{
	int bridge_count;

	bridge_count = 0;
	while (data->map[y][x] == '1')
		y++;
	while (data->map[y][x] == '0')
		bridge_count++;
	while (data->map[y] && data->map[y][x] == '1')
		y++;
	if (!data->map[y] && bridge_count < 4)
	{
		y = 0;
		while (data->map[y])
		{
			if (data->map[y][x] == '0')
				data->map[y][x] = 'B';
			else
				data->map[y][x] = 'R';
			y++;
		}
	}
}

void	check_empty_room(t_data *data, int x)
{
	int y;

	y = 0;
	while (data->map[y] && data->map[y][x] == '1' && data->map[y][x + 1])
		y++;
	if (data->map[y])
		return	;
	while (y >= 0)
		data->map[y--][x] = '3';
}

void	pillar_check(t_data *data, int x, int y)
{
	int y_original;

	y_original = y;
	while (data->map[y] && data->map[y][x] == '1')
		y++;
	if (!data->map[y] || y - y_original < 3)
		return	;
	while (y >= y_original)
		data->map[y--][x] = '3';
}

void	detect_map_objects(t_data *data, int x, int y)
{
	if (y == 1 && x && x != ft_strlen(data->map[y]))
		river_checker(data, x, y);
	if (y < data->map_y - 5 && data->map[y - 1][x] == '0')
		pillar_check(data, x, y);
	if (y == 1 && data->map[y][x] == '1')
		check_empty_room(data, x);
	statue_check(data, x, y);
}

void	wall_changer(t_data *data)
{
	int x;
	int y;

	y = 1;
	while(data->map[y + 1])
	{
		x = 0;
		while (data->map[y][x + 2])
		{
			if (data->map[y][x] == '1')
			{
				detect_map_objects(data, x, y);
			}
			x++;
		}
		y++;
	}
}