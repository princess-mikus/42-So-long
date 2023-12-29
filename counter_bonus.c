/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:04:21 by mikus             #+#    #+#             */
/*   Updated: 2023/12/29 14:32:11 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_numbers(t_window *win, t_images *images)
{
	int	a;
	int	b;

	images->black = \
	mlx_xpm_file_to_image(win->mlx, "textures/Misc/Black.xpm", &a, &b);
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
}

void	put_number(int nbr, t_window *win, t_data *data, t_images *images)
{
	int		i;
	int		offset;
	int		current;
	char	*number;

	if (!images->number[0])
		init_numbers(win, images);
	number = ft_itoa(nbr);
	offset = ft_strlen(number);
	i = -1;
	while (number[++i])
	{
		current = number[i] - 48;
		put_image(win, images->black, data->map_x - 2 - offset, -1);
		put_image(win, images->number[current], data->map_x - 2 - offset, -1);
		offset--;
	}
	free(number);
}
