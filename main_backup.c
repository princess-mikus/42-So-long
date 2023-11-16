/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:06:57 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/11/16 15:38:30 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	duplicate_validator(t_data *data)
{
	int	x;
	int	y;
	int	start;

	else if (data->map[y][x] == 'C')
	{
		if (images->coin)
			images->coins[j] = mlx_xpm_file_to_image(win->mlx, "sprites/Coin.xpm", &a, &b);
		printf("Coin %d: %p\n", j, images->coins[j]);
		mlx_put_image_to_window(win->mlx, win->pointer, images->coins[j++], x * 64, y * 64);
	}

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

int	key_hook(int keycode, t_data *data)
{
	printf("%d\n", keycode);
	if (keycode == 53)
	{
		printf("bYE!!!\n");
		exit (0);
	}
	if (keycode == 126 && data->map[data->player_y - 1][data->player_x] != '1')
	{
		printf("ARRIBA!!!\n");
		if (data->map[data->player_y - 1][data->player_x] == 'E')
			data->map[data->player_y - 1][data->player_x] = 'D';
		else if (data->map[data->player_y - 1][data->player_x] == 'C')
			data->coins--;
		data->map[data->player_y - 1][data->player_x] = 'P';
		data->map[data->player_y][data->player_x] = '0';
	}
	return (keycode);
}

int	update_map(void **temp)
{
	int 	y;
	int 	x;
	int 	i;
	t_window	*win 	= temp[0];
	t_data		*data 	= temp[1];
	t_images	*images	= temp[2];

	y = 0;
	x = 0;
	i = 0;
	int j = 0;
	int a;
	int b;
	static int c = 0;
	// Freeing things
	//while (i < data->coins && images->coins)
		//mlx_destroy_image(win->mlx, images->coins[i++]);
	//if (images->player)
		//mlx_destroy_image(win->mlx, images->player);
	//if (images->door)
	//	//mlx_destroy_image(win->mlx, images->door);
	i = 0;
	//while (i < c && images->walls)
	//	mlx_destroy_image(win->mlx, images->walls[i++]);
	i = 0;
	if (c)
		mlx_clear_window(win->mlx, win->pointer);
	c = 0;
	images->coins = malloc(data->coins * sizeof(void *));
	images->walls = malloc(data->map_y * data->map_x * sizeof(void *));
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'D')
				return(printf("WIN"));
			if (data->map[y][x] == '1')
			{
				images->walls[i] = mlx_xpm_file_to_image(win->mlx, "sprites/Wall_temp.xpm", &a, &b);
				mlx_put_image_to_window(win->mlx, win->pointer, images->walls[i++], x * 64, y * 64);
				c++;
			}
			if (data->map[y][x] == 'P')
			{
				images->player = mlx_xpm_file_to_image(win->mlx, "sprites/TEMMIE.xpm", &a, &b);
				mlx_put_image_to_window(win->mlx, win->pointer, images->player, x * 64, y * 64);
			}
			if (data->map[y][x] == 'E')
			{
				if (data->coins != '0')
					images->door = mlx_xpm_file_to_image(win->mlx, "sprites/Door_Closed.xpm", &a, &b);
				else
					images->door = mlx_xpm_file_to_image(win->mlx, "sprites/Door_Open.xpm", &a, &b);
				mlx_put_image_to_window(win->mlx, win->pointer, images->door, x * 64, y * 64 - 20);
			}
			else if (data->map[y][x] == 'C')
			{
				images->coins[j] = mlx_xpm_file_to_image(win->mlx, "sprites/Coin.xpm", &a, &b);
				mlx_put_image_to_window(win->mlx, win->pointer, images->coins[j++], x * 64, y * 64);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

void	create_window(t_data *data)
{
	t_window	win;
	t_images	images = {NULL, NULL, NULL, NULL};

	win.size_x = data->map_x * 64;
	win.size_y = data->map_y * 64;
	win.mlx = mlx_init();
	win.pointer = mlx_new_window(win.mlx, win.size_x, win.size_y, "hOI!!! i'm TEMMIE!!");
	win.background = mlx_xpm_file_to_image(win.mlx, "sprites/Background.xpm", &win.background_x, &win.background_y);
	mlx_put_image_to_window(win.mlx, win.pointer, win.background, 0, 0);
	/* Esto es una mierda, reemplazar por algo decente cuando duerma un poco */
	void	**temp = malloc(3 * sizeof(void *));
	temp[0] = &win;
	temp[1] = data;
	temp[2] = &images;
	mlx_key_hook(win.pointer, key_hook, temp);
	mlx_loop_hook(win.mlx, update_map, temp);
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
	while(data.map[i] != NULL)
	{
		//printf("%s", data.map[i]);
		data.map[++i] = get_next_line(fd);
		data.map_y++;
	}
	data.map_x = (int)ft_strlen(data.map[0]);
	printf("\n\n");
	if (!map_validator(&data))
		return(printf("RIP BOZO"));
	create_window(&data);
	system("leaks so_long");
	return (0);
}