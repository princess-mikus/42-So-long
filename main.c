/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:06:57 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/10/23 16:29:06 by fcasaubo         ###   ########.fr       */
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
	if (map[y][x] != '\n')
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

int map_validator(t_data *data)
{
	if (!wall_validator(data->map))
		return (0);
	if (!duplicate_validator(data))
		return (0);
	if (!path_validator(data))
		return (0);
	return (1);
}

int	key_hook(int keycode, t_window *win)
{
	if (keycode == 53)
	{
		mlx_destroy_window(win->mlx, win->pointer);
		printf("bYE!!!\n");
		exit (0);
	}
	// printf("%d\n", keycode);
	return (keycode);
}



void	create_window(t_data *data)
{
	t_window win;
	t_mlx	images;

	win.size_x = 1920;
	win.size_y = 1080;
	win.mlx = mlx_init();
	win.pointer = mlx_new_window(win.mlx, win.size_x, win.size_y, "hOI!!! i'm TEMMIE!!");
	win.background = mlx_xpm_file_to_image(win.mlx, "sprites/Background.xpm", &win.background_x, &win.background_y);
	mlx_put_image_to_window(win.mlx, win.pointer, win.background, 0, 0);
	mlx_key_hook(win.pointer, key_hook, &win);
	mlx_put_map(data, images);
	mlx_loop(win.mlx);
}

int main(int argc, char **argv)
{
	int		fd;
	int 	i;
	t_data	data;

	i = 0;
	if (argc > 2)
		return(perror(strerror(E2BIG)), 1);
	if (argc < 2)
		return(perror(strerror(EINVAL)), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror(strerror(ENOENT)), 1);
	data.map = malloc(4096 * sizeof(char **)); // Temporal, reemplazar por listas
	data.map[i] = get_next_line(fd);
	data.map_y = 1;
/*	while(data.map[i] != NULL)
	{
		printf("%s", data.map[i]);
		data.map[++i] = get_next_line(fd);
		data.map_y++;
	}*/
	printf("\n\n");
	if (map_validator(&data))
		return(perror(strerror(EINVAL)), 1);
	create_window(&data);
	return (0);
}