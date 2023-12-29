/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_updates_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:37:45 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/29 15:04:13 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	game_over(t_window *win, t_data *data, t_images *images)
{
	ft_printf("oH nO!!!! TEM IS KILL");
	close_game(win, data, images);
}

void	redraw_enemies(t_window *win, t_data *data, t_images *images)
{
	int			y;
	int			x;
	static int	i = 0;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == 'f')
				put_image(win, images->enemy_jumping, x, y - 1);
			if (data->map[y][x] == 'F' || data->map[y][x] == 'K')
			{
				if ((i++ / SPRITE_RATE) % 2)
					put_image(win, images->enemy[0], x, y - 1);
				else
					put_image(win, images->enemy[1], x, y - 1);
			}
		}
	}
	if (i == INT_MAX)
		i = 0;
}

void	draw_player(t_window *win, t_data *data, t_images *images)
{
	int			x;
	int			y;
	static int	i = 0;

	x = data->player_x;
	y = data->player_y;
	if (data->map[y][x] == 'k')
		game_over(win, data, images);
	if (data->map[y][x] == 'D')
	{
		if (data->coins == 0)
			check_win(win, data, images);
		else
			put_image(win, images->door_closed, x, y);
	}
	if (data->map[y][x] == 'c')
		put_image(win, images->coins, x, y);
	if ((i++ / SPRITE_RATE) % 2)
		put_image(win, images->player[0], x, y);
	else
		put_image(win, images->player[1], x, y);
	if (i == INT_MAX)
		i = 0;
	if (data->map[y][x] == 'K')
		redraw_enemies(win, data, images);
}

void	draw_coins(t_window *win, t_images *images, int x, int y)
{
	static int	i = 0;
	int			current;

	current = (i++ / (SPRITE_RATE * 20));
	if (current % 2)
		put_image(win, images->coins[1], x, y);
	else
		put_image(win, images->coins[2], x, y);
	if (i == 10000)
		i = 0;
}

void	update_map(t_window *win, t_data *data, t_images *images)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[++y + 1])
	{
		x = 0;
		while (data->map[y][++x + 1])
		{
			put_image(win, images->floor, x, y);
			if (data->map[y][x] == 'E' && data->coins == 0)
				put_image(win, images->door_open, x, y);
			else if (data->map[y][x] == 'E' || data->map[y][x] == 'D')
				put_image(win, images->door_closed, x, y);
			if (data->map[y][x] == 'c' || data->map[y][x] == 'p')
				put_image(win, images->coins_taken, x, y);
			if (data->map[y][x] == 'C')
				draw_coins(win, images, x, y);
		}
	}
	draw_inner_walls(win, data, images);
	draw_outter_walls(win, data, images);
	draw_player(win, data, images);
	redraw_enemies(win, data, images);
}
