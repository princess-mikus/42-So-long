/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_updates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:37:45 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/26 18:32:10 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
			if (data->map[y][x] == 'k')
				exit (0);
			if (data->map[y][x] != '1' && data->map[y][x] != '\n')
				put_image(win, images->floor, x, y);
			if (data->map[y][x] == 'F' || data->map[y][x] == 'K')
				put_image(win, images->enemy, x, y);
			if (data->map[y][x] == 'f' || data->map[y][x] == 'k')
				put_image(win, images->enemy_images.enemy_jumping, x, y);
			if (data->map[y][x] == 'E' && data->coins == 0)
				put_image(win, images->door_open, x, y);
			else if (data->map[y][x] == 'E' || data->map[y][x] == 'D')
				put_image(win, images->door_closed, x, y);
			if (data->map[y][x] == 'c' || data->map[y][x] == 'p')
				put_image(win, images->coins_taken, x, y);
			if (data->map[y][x] == 'P' || data->map[y][x] == 'D' || \
				data->map[y][x] == 'p' || data->map[y][x] == 'K' || \
				data->map[y][x] == 'k')
				put_image(win, images->player, x, y);
			if (data->map[y][x] == 'C')
				put_image(win, images->coins, x, y);
		}
	}
	draw_inner_walls(win, data, images);
}
