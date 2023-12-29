/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:50:43 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/29 15:07:37 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_numbers(t_window *win, t_images *images)
{
	int	i;

	i = 0;
	while (i <= 9)
		mlx_destroy_image(win->mlx, images->number[i++]);
}

void	free_images(t_window *win, t_images *images)
{
	mlx_destroy_image(win->mlx, images->wall);
	mlx_destroy_image(win->mlx, images->left_corner);
	mlx_destroy_image(win->mlx, images->right_corner);
	mlx_destroy_image(win->mlx, images->middle_corner);
	mlx_destroy_image(win->mlx, images->upper_left_corner);
	mlx_destroy_image(win->mlx, images->upper_right_corner);
	mlx_destroy_image(win->mlx, images->upper_middle_corner);
	mlx_destroy_image(win->mlx, images->left_wall);
	mlx_destroy_image(win->mlx, images->right_wall);
	mlx_destroy_image(win->mlx, images->player[0]);
	mlx_destroy_image(win->mlx, images->player[1]);
	mlx_destroy_image(win->mlx, images->floor);
	mlx_destroy_image(win->mlx, images->door_open);
	mlx_destroy_image(win->mlx, images->door_closed);
	mlx_destroy_image(win->mlx, images->coins[0]);
	mlx_destroy_image(win->mlx, images->coins[1]);
	mlx_destroy_image(win->mlx, images->coins[2]);
	mlx_destroy_image(win->mlx, images->enemy[0]);
	mlx_destroy_image(win->mlx, images->enemy[1]);
	mlx_destroy_image(win->mlx, images->enemy_jumping);
	mlx_destroy_image(win->mlx, images->black);
	free_numbers(win, images);
	mlx_destroy_image(win->mlx, images->coins_taken);
	mlx_destroy_image(win->mlx, images->floor);
}

void	free_window(t_window *win)
{
	mlx_destroy_image(win->mlx, win->background);
	mlx_destroy_window(win->mlx, win->ptr);
	free(win->mlx);
}

void	close_game(t_window *win, t_data *data, t_images *images)
{
	free_images(win, images);
	free_window(win);
	free_array((void *)data->map);
	exit (0);
}

void	check_win(t_window *win, t_data *data, t_images *images)
{
	int	x;
	int	y;

	x = data->player_x;
	y = data->player_y;
	if (!(data->map[y][x] == 'D') || data->coins)
		return ;
	else
		close_game(win, data, images);
}
