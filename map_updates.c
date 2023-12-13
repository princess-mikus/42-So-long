/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_updates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:37:45 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/13 13:56:20 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_map(t_window *win, t_data *data, t_images *images)
{
	int	y;
	int	x;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] != '1' && data->map[y][x] != '\n')
				put_image(win, images->floor, x, y);
			if (data->map[y][x] == 'E' && data->coins == 0)
				put_image(win, images->door_open, x, y);
			else if (data->map[y][x] == 'E' || data->map[y][x] == 'D')
				put_image(win, images->door_closed, x, y);
			if (data->map[y][x] == 'c' || data->map[y][x] == 'p')
				put_image(win, images->coins_taken, x, y);
			if (data->map[y][x] == 'P' || data->map[y][x] == 'D' || \
				data->map[y][x] == 'p')
				put_image(win, images->player, x, y);
			if (data->map[y][x] == 'C')
				put_image(win, images->coins, x, y);
		}
	}
	draw_inner_walls(win, data, images);
}
