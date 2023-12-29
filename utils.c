/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:02:23 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/29 15:07:40 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_window	*win, void	*img, int x, int y)
{
	mlx_put_image_to_window \
	(win->mlx, win->ptr, img, (x * 64) + 64, (y * 64) + 64);
}

void	free_array(void **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	close_window(void **structures)
{
	close_game(structures[0], structures[1], structures[2]);
	return (1);
}
