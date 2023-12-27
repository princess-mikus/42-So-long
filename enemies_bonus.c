/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:54:52 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/27 19:15:11 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	spawn_single_enemy(t_data *data)
{
	int			random_x;
	int			random_y;

	random_x = rand() % data->map_x;
	random_y = rand() % (data->map_y - 3);
	if (data->map[random_y][random_x] == '0')
		data->map[random_y][random_x] = 'F';
	else
		spawn_single_enemy(data);
	return ;
}

int	count_walls(char **map)
{
	int	y;
	int	x;
	int	walls;

	walls = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '1')
				walls++;
	}
	return (walls);
}

int	count_floors(char	**map)
{
	int	y;
	int	x;
	int	floors;

	y = -1;
	floors = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '0')
				floors++;
	}
	return (floors);
}

void	init_enemies(t_window *window, t_images *images)
{
	int	a;
	int	b;

	images->enemy = \
	mlx_xpm_file_to_image(window->mlx, "textures/Enemy/Enemy_idle.xpm", &a, &b);
	images->enemy_images.enemy_jumping = \
	mlx_xpm_file_to_image(window->mlx, \
	"textures/Enemy/Enemy_jumping.xpm", &a, &b);
	images->player_dead[0] = \
	mlx_xpm_file_to_image(window->mlx, "textures/Player/Dead1.xpm", &a, &b);
	images->player_dead[1] = \
	mlx_xpm_file_to_image(window->mlx, "textures/Player/Dead2.xpm", &a, &b);
	images->game_over = \
	mlx_xpm_file_to_image(window->mlx, "textures/Misc/Game_over.xpm", &a, &b);
}

void	spawn_enemies(t_data *data)
{
	int	walls;
	int	area;

	data->enemy_count = 0;
	walls = count_walls(data->map);
	area = (data->map_y - 2) * data->map_x - walls;
	while ((area % ENEMY_RATE != area \
	|| data->enemy_count <= 0) && count_floors(data->map) > data->enemy_count)
	{
		spawn_single_enemy(data);
		area /= ENEMY_RATE;
		data->enemy_count++;
	}
}
