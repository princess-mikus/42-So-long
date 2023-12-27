/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:04:21 by mikus             #+#    #+#             */
/*   Updated: 2023/12/27 19:12:27 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	put_number(int nbr, t_window *win, t_data *data, t_images *images)
{
	int		i;
	int		offset;
	int		current;
	char	*number;

	i = 0;
	number = itoa(nbr);
	offset = ft_strlen(number);
	while (number[i])
	{
		put_image(win, images->black, data->map_x - offset - 64, -64);
		current = number[i] - 48;
		put_image(win, images->number[current], data->map_x - offset - 64, -64);
		offset--;
	}
	free(number);
}

void	init_numbers(t_window *win, t_images *images)
{
	int	a;
	int	b;

	images->number[0] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Numbers/0.xpm", &a, &b);
	images->number[1] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Numbers/1.xpm", &a, &b);
	images->number[2] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Numbers/2.xpm", &a, &b);
	images->number[3] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Numbers/3.xpm", &a, &b);
	images->number[4] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Numbers/4.xpm", &a, &b);
	images->number[5] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Numbers/5.xpm", &a, &b);
	images->number[6] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Numbers/6.xpm", &a, &b);
	images->number[7] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Numbers/7.xpm", &a, &b);
	images->number[8] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Numbers/8.xpm", &a, &b);
	images->number[9] = \
	mlx_xpm_file_to_image(win->mlx, "textures/Numbers/9.xpm", &a, &b);
	images->black = \
	mlx_xpm_file_to_image(win->mlx, "textures/Misc/Black.xpm", &a, &b);
}
