/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:29:13 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/18 16:34:13 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	execute_jump(t_data *data, int vertical, int horizontal)
{
	srand(time(NULL));
	if (rand() % 100 <= JUMP_CHANCE)
	{
		data->map[vertical][horizontal] = 'f';
		return (1);
	}
	return (0);
}

void	move_enemy(int *enemy_x, int *enemy_y, int *count)
{
	int			random;
	int			direction;

	srand(time(NULL) + *count++);
	direction = rand() % 2;
	random = rand() % 2;
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

void	enemy_movement(t_data *data, int enemy_x, int enemy_y, int *count)
{
	int			new_x;
	int			new_y;
	int			count2;

	if (execute_jump(data, enemy_x, enemy_y))
		return ;
	new_x = enemy_x;
	new_y = enemy_y;
	count = 0;
	while (data->map[new_x][new_y] != '0' || *count++ < 10)
	{
		new_x = 0;
		new_y = 0;
		move_enemy(&new_x, &new_y, &count2);
	}
	if (rand() % 100 <= MOVEMENT_CHANCE)
		data->map[new_y][new_x] = 'F';
	count = 0;
}
