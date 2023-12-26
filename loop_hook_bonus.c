/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:47:02 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/26 18:27:04 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	search_enemies(t_data	*data)
{
	int			y;
	int			x;
	static int	count = 0;

	y = -1;
	while (data->map[++y] && (data->enemy_count > count \
	|| count == 0))
	{
		x = -1;
		while (data->map[y][++x] && (data->enemy_count > count || count == 0))
		{
			if (data->map[y][x] == 'f')
				data->map[y][x] = 'F';
			else if (data->map[y][x] == 'F' || data->map[y][x] == 'K')
			{
				enemy_movement(data, x, y);
				count++;
			}
		}
	}
	count = 0;
}

void	redraw_enemies(t_window *window, t_data	*data, t_images *images)
{
	int	y;
	int	x;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == 'f')
				put_image(window->ptr, \
				images->enemy_images.enemy_jumping, x, y);
		}
	}
}

int	loop_hook(void **structures)
{
	t_window	*win;
	t_data		*data;
	t_images	*images;

	win = structures[0];
	data = structures[1];
	images = structures[2];
	if (data->tick == TICK_RATE)
	{
		search_enemies(data);
		data->tick = 0;
	}
	update_map(structures[0], structures[1], structures[2]);
	data->tick++;
	return (0);
}
