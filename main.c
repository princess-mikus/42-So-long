/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:06:57 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/07 15:51:40 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	duplicate_validator(t_data *data)
{
	int	x;
	int	y;
	int	start;

	y = 0;
	start = 0;
	while (data->map[y] != NULL)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] == 'P')
			{
				start++;
				data->player_x = x;
				data->player_y = y;
			}
			if (data->map[y][x] == 'E')
				data->exit++;
			if (data->map[y][x] == 'C')
				data->coins++;
			x++;
		}
		y++;
	}
	if (start != 1 || data->exit != 1)
		return (0);
	return (1);
}

int wall_validator(char **map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (map[y][x] == '1')
		x++;
	if (map[y][x])
		return (0);
	x--;
	while (map[y + 1] != NULL)
	{
		if (map[y][0] != '1' || map[y][x] != '1')
			return (0);
		y++;
	}
	while (map[y][x] == '1')
		x++;
	if (map[y][x] != '\0')
		return (0);
	return (1);
}

int	map_validator(t_data *data)
{
	if (!wall_validator(data->map))
		return (0);
	if (!duplicate_validator(data))
		return (0);
	if (!path_validator(data))
		return (0);
	return (1);
}
/*
void	draw_pillars(t_data	*data, t_window	*win, t_images *images, int x, int y)
{
	while(data->map[x][y + 1] == '1')
		y++;
	mlx_put_image_to_window(win->mlx, win->ptr, images->pillar_base, (x * 64) + 64, ( * 64) + 64);
	data->map[x][y] = '2';
	while (data->map[y + 1] == '1')
		mlx_put_image_to_window(win->mlx, win->ptr, images->pillar_middle, (x * 64) + 64, (y * 64) + 64);
	mlx_put_image_to_window(win->mlx, win->ptr, images->pillar_top, (x * 64) + 64, (y * 64) + 64);
	data->map[x][y] = '2';
}
*/
void	draw_walls(t_window *win, t_data *data, t_images *images)
{
	int y;
	int	x;
	//int coord[2];

	y = data->map_y - 3;
	while (y >= 0)
	{
		x = (int)ft_strlen(data->map[y]);
		while (x >= 0)
		{
			if (data->map[y][x] == '1')
			{
				if (x == 0 && y == data->map_y - 3)
					mlx_put_image_to_window(win->mlx, win->ptr, images->left_corner, (x * 64) + 64, (y * 64) + 64);
				else if (x == 0 && y == 0)
					mlx_put_image_to_window(win->mlx, win->ptr, images->upper_left_corner, (x * 64) + 64, (y * 64) + 64);
				else if (x == 0)
					mlx_put_image_to_window(win->mlx, win->ptr, images->left_wall, (x * 64) + 64, (y * 64) + 64);
				else if (x == (int)ft_strlen(data->map[y]) - 1 && y == data->map_y - 3)
					mlx_put_image_to_window(win->mlx, win->ptr, images->right_corner, (x * 64) + 64, (y * 64) + 64);
				else if (x == (int)ft_strlen(data->map[y]) - 1 && y == 0)
					mlx_put_image_to_window(win->mlx, win->ptr, images->upper_right_corner, (x * 64) + 64, (y * 64) + 64);
				else if (x == (int)ft_strlen(data->map[y]) - 1)
					mlx_put_image_to_window(win->mlx, win->ptr, images->right_wall, (x * 64) + 64, (y * 64) + 64);
				else if (y == data->map_y - 3)
					mlx_put_image_to_window(win->mlx, win->ptr, images->middle_corner, (x * 64) + 64, (y * 64) + 64);
				else if (y == 0)
					mlx_put_image_to_window(win->mlx, win->ptr, images->upper_middle_corner, (x * 64) + 64, (y * 64) + 64);
				else
				{
					mlx_put_image_to_window(win->mlx, win->ptr, images->floor, (x * 64) + 64, (y * 64) + 64);
					//draw_pillars(data, win, images, x, y);
				}
			}
			x--;
		}
		y--;
	}
}

void	update_map(t_window *win, t_data *data, t_images *images)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'D' && data->coins < 1)
				exit (0);
			else if (data->map[y][x] != '1' && data->map[y][x] != '\n')
				mlx_put_image_to_window(win->mlx, win->ptr, images->floor, (x * 64) + 64, (y * 64) + 64);
			if (data->map[y][x] == 'E' || data->map[y][x] == 'D')
			{
				if (data->coins == 0)
					mlx_put_image_to_window(win->mlx, win->ptr, images->door_open, (x * 64) + 64, (y * 64) + 64 - 20);
				else
					mlx_put_image_to_window(win->mlx, win->ptr, images->door_closed, (x * 64) + 64, (y * 64) + 64 - 20);
			}
			if (data->map[y][x] == 'P' || data->map[y][x] == 'D')
				mlx_put_image_to_window(win->mlx, win->ptr, images->player, (x * 64) + 64, (y * 64) + 64);
			if (data->map[y][x] == 'C')
				mlx_put_image_to_window(win->mlx, win->ptr, images->coins, (x * 64) + 64, (y * 64) + 64);
			x++;
		}
		x = 0;
		y++;
	}
	draw_walls(win, data, images);
}

void	init_outter_walls(t_window *win, t_images *images)
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
}

void	create_map(void **temp)
{
	t_window	*win;
	t_images	*images;
	int			a;
	int			b;

	win = temp[0];
	images = temp[2];
	images->door_open = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Door_Open.xpm", &a, &b);
	images->door_closed = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Door_Closed.xpm", &a, &b);
	images->coins = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Coin.xpm", &a, &b);
	images->player = \
	mlx_xpm_file_to_image(win->mlx, "sprites/TEMMIE.xpm", &a, &b);
	images->floor = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Floor_placeholder.xpm", &a, &b);
	images->wall = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Statue.xpm", &a, &b);
	images->upper_right_corner = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Right_upper_corner.xpm", &a, &b);
	// Remember to do a function that draw walls, as they don't change really
	init_outter_walls(win, images);
	update_map(temp[0], temp[1], temp[2]);
}

void	create_window(void **temp)
{
	t_window	*win;
	t_data		*data;
	t_images	*images;

	win = temp[0];
	data = temp[1];
	images = temp[2];
	win->size_x = data->map_x * 64;
	win->size_y = data->map_y * 64;
	win->mlx = mlx_init();
	win->ptr = \
	mlx_new_window(win->mlx, win->size_x, win->size_y, "hOI!!! i'm TEMMIE!!");
	win->background = mlx_xpm_file_to_image \
	(win->mlx, "sprites/Background.xpm", &win->bg_x, &win->bg_y);
	mlx_put_image_to_window(win->mlx, win->ptr, win->background, 0, 0);
	images->coins = malloc((data->coins) * sizeof(void *));
	images->floor = malloc(4096 * sizeof(void *));
	create_map(temp);
	mlx_key_hook(win->ptr, key_hook, temp);
	mlx_loop(win->mlx);
}

int main(int argc, char **argv)
{
	int			fd;
	int 		i;
	t_data		data;
	t_window	win;
	t_images	images;
	void		*temp[3];
	char		*temp2;

	data.movements = 1;
	temp[0] = &win;
	temp[1] = &data;
	temp[2] = &images;
	if (argc > 2)
		return(perror(strerror(E2BIG)), 1);
	if (argc < 2)
		return(perror(strerror(EINVAL)), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror(strerror(ENOENT)), 1);
	data.map = malloc(4096 * sizeof(char **)); // Temporal, reemplazar por listas
	i = 0;
	temp2 = get_next_line(fd);
	data.map[i] = ft_strtrim(temp2, "\n");
	free(temp2);
	data.map_y = 2;
	while (data.map[i] != NULL)
	{
		temp2 = get_next_line(fd);
		data.map[++i] = ft_strtrim(temp2, "\n");
		free(temp2);
		data.map_y++;
	}
	i = 0;
	while (data.map[i])
	{
		printf("%s\n", data.map[i++]);
	}
	data.map_x = (int)ft_strlen(data.map[0]) + 2;
	if (!map_validator(&data))
		return(printf("RIP BOZO"));
	create_window(temp);
	return (0);
}