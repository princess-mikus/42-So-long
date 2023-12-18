/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:47:02 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/18 17:02:20 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	search_enemies(t_data	*data)
{
	int	y;
	int	x;
	int	count;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			count = 0;
			if (data->map[y][x] == 'f')
				data->map[y][x] = 'F';
			else if (data->map[y][x] == 'F')
				enemy_movement(data, x, y, &count);
		}
	}
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
			else if (data->map[y][x] == 'F')
				printf("Animation change\n");
		}
	}
}

int	loop_hook(void)
{
	/*
	t_window	*win;
	t_data		*data;
	t_images	*images;

	win = structures[0];
	data = structures[1];
	images = structures[2];
	if (win && data && images)
	{
		printf("hii\n");
		return (0);
	}
	if (data->tick == TICK_RATE)
	{
		search_enemies(data);
		data->tick = 0;
	}
	if (!data->tick % 30)
		redraw_enemies(win, data, images);
	data->tick++;
	if (data->tick == 100)
		printf("%d\n", data->tick);
	*/
	write(1, "Hola", 4);
	return (0); 
}
