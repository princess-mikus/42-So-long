/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:06:57 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/29 15:14:01 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_map(void **structures)
{
	t_window	*win;
	t_images	*images;
	int			a;
	int			b;

	win = structures[0];
	images = structures[2];
	images->door_open = \
	mlx_xpm_file_to_image(win->mlx, "textures/Map/Door_Open.xpm", &a, &b);
	images->door_closed = \
	mlx_xpm_file_to_image(win->mlx, "textures/Map/Door_Closed.xpm", &a, &b);
	images->coins = \
	mlx_xpm_file_to_image(win->mlx, "textures/Map/Coin.xpm", &a, &b);
	images->coins_taken = \
	mlx_xpm_file_to_image(win->mlx, "textures/Map/Coin_taken.xpm", &a, &b);
	images->player = \
	mlx_xpm_file_to_image(win->mlx, "textures/Player/Player.xpm", &a, &b);
	images->floor = \
	mlx_xpm_file_to_image(win->mlx, "textures/Map/Floor.xpm", &a, &b);
	draw_outter_walls(structures[0], structures[1], structures[2]);
	update_map(structures[0], structures[1], structures[2]);
}

void	create_window(void **structures)
{
	t_window	*win;
	t_data		*data;

	win = structures[0];
	data = structures[1];
	win->size_x = data->map_x * 64;
	win->size_y = data->map_y * 64;
	win->mlx = mlx_init();
	win->ptr = \
	mlx_new_window(win->mlx, win->size_x, win->size_y, "hOI!!! i'm TEMMIE!!");
	win->background = mlx_xpm_file_to_image \
	(win->mlx, "textures/Misc/Background.xpm", &win->bg_x, &win->bg_y);
	init_walls(win, structures[2]);
	put_image(win, win->background, 0, 0);
	create_map(structures);
	mlx_key_hook(win->ptr, key_hook, structures);
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

	data.movements = 1;
	structures[0] = &win;
	structures[1] = &data;
	structures[2] = &images;
	argument_checker(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_printf("So long: Error, map not found"));
	import_map(&data, fd);
	data.map_x = (int)ft_strlen(data.map[0]) + 2;
	if (!map_validator(&data))
		return (-1);
	close(fd);
	create_window(structures);
	return (0);
}
