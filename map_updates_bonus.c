/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_updates_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:37:45 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/27 18:18:51 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	draw_game_over(t_window *win, t_data *data, t_images *images)
{
	put_image(win, images->player_dead[0], data->player_x, data->player_y);
	sleep(1);
	put_image(win, images->black, data->player_x, data->player_y);
	put_image(win, images->player_dead[1], data->player_x, data->player_y);
	sleep(1);
	put_image(win, images->game_over, \
	(data->map_x * 64) / 2, (data->map_y * 64) / 2);
}

void	game_over(t_window *win, t_data *data, t_images *images)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
			put_image(win, images->black, x, y);
	}
	ft_printf("oH nO!!!! TEM IS KIL");
	draw_game_over(win, data, images);
	sleep(5);
	close_game(win, data, images);
}

void	draw_player(t_window *win, t_data *data, t_images *images)
{
	int	x;
	int	y;

	x = data->player_x;
	y = data->player_y;
	if (data->map[y][x] == 'k')
	{
		put_image(win, images->enemy_images.enemy_jumping, x, y);
		put_image(win, images->player, x, y);
		game_over(win, data, images);
	}
	if (data->map[y][x] == 'D')
	{
		if (data->coins == 0)
			check_win(win, data, images);
		else
			put_image(win, images->door_closed, x, y);
	}
	if (data->map[y][x] == 'c')
		put_image(win, images->coins, x, y);
	put_image(win, images->player, x, y);
}

void	redraw_enemies(t_window *win, t_data	*data, t_images *images)
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
				put_image(win->ptr, \
				images->enemy_images.enemy_jumping, x, y);
			if (data->map[y][x] == 'F')
				put_image(win->ptr, \
				images->enemy, x, y);
		}
	}
}

void	update_map(t_window *win, t_data *data, t_images *images)
{
	int	y;
	int	x;

	y = -1;
	draw_player(win, data, images);
	redraw_enemies(win, data, images);
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] != '1')
				put_image(win, images->floor, x, y);
			if (data->map[y][x] == 'E' && data->coins == 0)
				put_image(win, images->door_open, x, y);
			else if (data->map[y][x] == 'E' || data->map[y][x] == 'D')
				put_image(win, images->door_closed, x, y);
			if (data->map[y][x] == 'c' || data->map[y][x] == 'p')
				put_image(win, images->coins_taken, x, y);
			if (data->map[y][x] == 'C')
				put_image(win, images->coins, x, y);
		}
	}
	draw_inner_walls(win, data, images);
}
