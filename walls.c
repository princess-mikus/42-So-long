/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:33:39 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/13 13:58:45 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_inner_walls(t_window *win, t_data *data, t_images *images)
{
	int	y;
	int	x;

	y = 1;
	while (data->map[y + 1])
	{
		x = 1;
		while (data->map[y][x + 1])
		{
			if (data->map[y][x] == '1')
			{
				put_image(win, images->floor, x, y);
				put_image(win, images->wall, x, y);
			}
			x++;
		}
		y++;
	}
}

void	draw_wall(t_window *win, t_data *data, \
		t_images *images, int *coordinates)
{
	int	x;
	int	y;

	x = coordinates[0];
	y = coordinates[1];
	if (data->map[y][x] == '1')
	{
		if (x == 0 && y == data->map_y - 3)
			put_image(win, images->left_corner, x, y);
		else if (x == 0 && y == 0)
			put_image(win, images->upper_left_corner, x, y);
		else if (x == 0)
			put_image(win, images->left_wall, x, y);
		else if (x == (int)ft_strlen(data->map[y]) - 1 && y == data->map_y - 3)
			put_image(win, images->right_corner, x, y);
		else if (x == (int)ft_strlen(data->map[y]) - 1 && y == 0)
			put_image(win, images->upper_right_corner, x, y);
		else if (x == (int)ft_strlen(data->map[y]) - 1)
			put_image(win, images->right_wall, x, y);
		else if (y == data->map_y - 3)
			put_image(win, images->middle_corner, x, y);
		else if (y == 0)
			put_image(win, images->upper_middle_corner, x, y);
	}
}

void	init_walls(t_window *win, t_images *images)
{
	int	a;
	int	b;

	images->right_corner = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Right_corner.xpm", &a, &b);
	images->left_corner = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Left_corner.xpm", &a, &b);
	images->upper_left_corner = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Left_upper_corner.xpm", &a, &b);
	images->middle_corner = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Middle_corner.xpm", &a, &b);
	images->upper_middle_corner = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Upper_middle_corner.xpm", &a, &b);
	images->left_wall = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Left_wall.xpm", &a, &b);
	images->right_wall = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Right_wall.xpm", &a, &b);
	images->wall = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Wall.xpm", &a, &b);
}

void	draw_outter_walls(t_window *win, t_data *data, t_images *images)
{
	int	y;
	int	x;
	int	coordinates[2];

	y = -1;
	init_walls(win, images);
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			coordinates[0] = x;
			coordinates[1] = y;
			draw_wall(win, data, images, coordinates);
		}
	}
}
