/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:42:35 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/18 16:50:06 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	create_map(void **structures)
{
	t_window	*win;
	t_images	*images;
	int			a;
	int			b;

	win = structures[0];
	images = structures[2];
	images->door_open = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Door_Open.xpm", &a, &b);
	images->door_closed = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Door_Closed.xpm", &a, &b);
	images->coins = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Coin.xpm", &a, &b);
	images->coins_taken = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Coin_taken.xpm", &a, &b);
	images->player = \
	mlx_xpm_file_to_image(win->mlx, "sprites/TEMMIE.xpm", &a, &b);
	images->floor = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Floor_placeholder.xpm", &a, &b);
	images->wall = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Statue.xpm", &a, &b);
	images->enemy = \
	mlx_xpm_file_to_image(win->mlx, "sprites/Placeholder_coin.xpm", &a, &b);
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
	(win->mlx, "sprites/Background.xpm", &win->bg_x, &win->bg_y);
	put_image(win, win->background, 0, 0);
	images->coins = malloc((data->coins) * sizeof(void *));
	images->floor = malloc(4096 * sizeof(void *));
	spawn_enemies(data);
	init_enemies(win, images);
	create_map(structures);
	data->tick = 0;
	mlx_key_hook(win->ptr, key_hook, structures);
	mlx_loop_hook(win->ptr, loop_hook, NULL);
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
		return (perror(strerror(ENOENT)), 1);
	import_map(&data, fd);
	data.map_x = (int)ft_strlen(data.map[0]) + 2;
	if (!map_validator(&data))
		return (-1);
	create_window(structures);
	return (0);
}
