/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:29:13 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/29 15:02:18 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	execute_jump(t_data *data, int horizontal, int vertical)
{
	if (get_random_number() % 100 <= JUMP_CHANCE)
	{
		if (data->map[vertical][horizontal] == 'K')
			data->map[vertical][horizontal] = 'k';
		else
			data->map[vertical][horizontal] = 'f';
		return (1);
	}
	return (0);
}

void	move_enemy(int *enemy_x, int *enemy_y)
{
	int			random;
	int			direction;

	direction = get_random_number() % 2;
	random = get_random_number() % 2;
	if (direction)
	{
		if (random)
			*enemy_y += 1;
		else
			*enemy_y -= 1;
	}
	else
	{
		if (random)
			*enemy_x += 1;
		else
			*enemy_x -= 1;
	}
}

void	enemy_movement(t_data *data, int enemy_x, int enemy_y)
{
	int			new_x;
	int			new_y;
	static int	count = 0;

	if (execute_jump(data, enemy_x, enemy_y))
		return ;
	new_x = enemy_x;
	new_y = enemy_y;
	while (data->map[new_y][new_x] != '0' && count++ < 10)
	{
		new_x = enemy_x;
		new_y = enemy_y;
		move_enemy(&new_x, &new_y);
	}
	if (get_random_number() % 100 <= MOVEMENT_CHANCE \
	&& data->map[new_y][new_x] == '0' && count != 10)
	{
		data->map[enemy_y][enemy_x] = '0';
		data->map[new_y][new_x] = 'F';
	}
	count = 0;
}
