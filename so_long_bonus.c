/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:42:35 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/29 15:09:19 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_player_and_coins(void **structures)
{
	t_window	*win;
	t_data		*data;
	t_images	*images;
	int			a;
	int			b;

	win = structures[0];
	data = structures[1];
	images = structures[2];
	images->player[0] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Player/Player.xpm", &a, &b);
	images->player[1] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Player/Player2.xpm", &a, &b);
	images->coins[0] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Map/Coin.xpm", &a, &b);
	images->coins[1] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Map/Coin2.xpm", &a, &b);
	images->coins[2] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Map/Coin3.xpm", &a, &b);
}

void	create_map(void **structures)
{
	t_window	*win;
	t_data		*data;
	t_images	*images;
	int			a;
	int			b;

	win = structures[0];
	data = structures[1];
	images = structures[2];
	init_player_and_coins(structures);
	images->door_open = \
	mlx_xpm_file_to_image(win->mlx, "textures/Map/Door_Open.xpm", &a, &b);
	images->door_closed = \
	mlx_xpm_file_to_image(win->mlx, "textures/Map/Door_Closed.xpm", &a, &b);
	images->coins_taken = \
	mlx_xpm_file_to_image(win->mlx, "textures/Map/Coin_taken.xpm", &a, &b);
	images->floor = \
	mlx_xpm_file_to_image(win->mlx, "textures/Map/Floor.xpm", &a, &b);
	images->wall = \
	mlx_xpm_file_to_image(win->mlx, "textures/Walls/Wall.xpm", &a, &b);
	draw_outter_walls(structures[0], structures[1], structures[2]);
	update_map(structures[0], structures[1], structures[2]);
}

void	create_window(void **structures)
{
	t_window	*win;
	t_data		*data;
	t_images	*images;

	win = structures[0];
	data = structures[1];
	images = structures[2];
	win->size_x = data->map_x * 64;
	win->size_y = data->map_y * 64;
	win->mlx = mlx_init();
	win->ptr = \
	mlx_new_window(win->mlx, win->size_x, win->size_y, "hOI!!! i'm TEMMIE!!");
	win->background = mlx_xpm_file_to_image \
	(win->mlx, "textures/Misc/Background.xpm", &win->bg_x, &win->bg_y);
	put_image(win, win->background, 0, 0);
	put_number(data->movements, win, data, images);
	init_walls(win, images);
	init_enemies(win, images);
	spawn_enemies(data);
	create_map(structures);
	data->tick = 0;
	mlx_key_hook(win->ptr, key_hook, structures);
	mlx_loop_hook(win->mlx, loop_hook, structures);
	mlx_hook(win->ptr, 17, 0, close_window, structures);
	mlx_loop(win->mlx);
}

void	argument_checker(int argc, char **argv)
{
	char	*str;
	size_t	i;

	if (argc > 2)
	{
		ft_printf("so_long: Error, too many arguments\n");
		exit(7);
	}
	if (argc < 2)
	{
		ft_printf("so_long: Error, too few arguments\n");
		exit(22);
	}
	str = argv[1];
	i = ft_strlen(str) - 1;
	if (str[i - 3] != '.' || str[i - 2] != 'b' || \
	str[i - 1] != 'e' || str[i] != 'r')
	{
		ft_printf("so_long: Error, map not .ber\n");
		exit(22);
	}
}

int	main(int argc, char **argv)
{
	int			fd;
	t_data		data;
	t_window	win;
	t_images	images;
	void		*structures[3];

	structures[0] = &win;
	structures[1] = &data;
	structures[2] = &images;
	argument_checker(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror(strerror(ENOENT)), 1);
	import_map(&data, fd);
	data.map_x = (int)ft_strlen(data.map[0]) + 2;
	images.number[0] = NULL;
	images.wall = NULL;
	if (!map_validator(&data))
		return (-1);
	create_window(structures);
	return (0);
}
