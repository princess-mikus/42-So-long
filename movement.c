/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:52:14 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/05 12:24:29 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	movement_up(t_data *data, int x, int y)
{
	if (data->map[y - 1][x] == 'E')
		data->map[y - 1][x] = 'D';
	else
	{
		if (data->map[y - 1][x] == 'C' || data->map[y - 1][x] == 'c')
		{
			if (data->map[y - 1][x] == 'C')
				data->coins--;
			data->map[y - 1][x] = 'p';
		}
		else
			data->map[y - 1][x] = 'P';
	}
	data->player_y--;
	if (data->map[y][x] == 'D')
		data->map[y][x] = 'E';
	else if (data->map[y][x] == 'p')
		data->map[y][x] = 'c';
	else
		data->map[y][x] = '0';
}

void	movement_down(t_data *data, int x, int y)
{
	if (data->map[y + 1][x] == 'E')
		data->map[y + 1][x] = 'D';
	else
	{
		if (data->map[y + 1][x] == 'C' || data->map[y + 1][x] == 'c')
		{
			if (data->map[y + 1][x] == 'C')
				data->coins--;
			data->map[y + 1][x] = 'p';
		}
		else
			data->map[y + 1][x] = 'P';
	}
	data->player_y++;
	if (data->map[y][x] == 'D')
		data->map[y][x] = 'E';
	else if (data->map[y][x] == 'p')
		data->map[y][x] = 'c';
	else
		data->map[y][x] = '0';
}

void	movement_left(t_data *data, int x, int y)
{
	if (data->map[y][x - 1] == 'E')
		data->map[y][x - 1] = 'D';
	else
	{
		if (data->map[y][x - 1] == 'C' || data->map[y][x - 1] == 'c')
		{
			if (data->map[y][x - 1] == 'C')
				data->coins--;
			data->map[y][x - 1] = 'p';
		}
		else
			data->map[y][x - 1] = 'P';
	}
	data->player_x--;
	if (data->map[y][x] == 'D')
		data->map[y][x] = 'E';
	else if (data->map[y][x] == 'p')
		data->map[y][x] = 'c';
	else
		data->map[y][x] = '0';
}

void	movement_right(t_data *data, int x, int y)
{
	if (data->map[y][x + 1] == 'E')
		data->map[y][x + 1] = 'D';
	else
	{
		if (data->map[y][x + 1] == 'C' || data->map[y][x + 1] == 'c')
		{
			if (data->map[y][x + 1] == 'C')
				data->coins--;
			data->map[y][x + 1] = 'p';
		}
		else
			data->map[y][x + 1] = 'P';
	}
	data->player_x++;
	if (data->map[y][x] == 'D')
		data->map[y][x] = 'E';
	else if (data->map[y][x] == 'p')
		data->map[y][x] = 'c';
	else
		data->map[y][x] = '0';
}

int	key_hook(int keycode, void **temp)
{
	int		x;
	int		y;
	t_data	*data;

	data = temp[1];
	x = data->player_x;
	y = data->player_y;
	if (keycode == 53)
		exit (0);
	if (keycode == 13 && data->map[y - 1][x] != '1')
		movement_up(data, x, y);
	if (keycode == 1 && data->map[y + 1][x] != '1')
		movement_down(data, x, y);
	if (keycode == 0 && data->map[y][x - 1] != '1')
		movement_left(data, x, y);
	if (keycode == 2 && data->map[y][x + 1] != '1')
		movement_right(data, x, y);
	if (x != data->player_x || y != data->player_y)
	{
		if (data->movements < INT_MAX)
			ft_printf("%d\n", ++data->movements);
		update_map(temp[0], temp[1], temp[2]);
	}
	return (keycode);
}
