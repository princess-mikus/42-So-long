/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:45:31 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/26 12:03:07 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	get_random_number(void)
{
	static int	fd = 0;
	char		buffer[10];
	int			number;
	int			i;

	if (!fd)
		fd = open("/dev/random", O_RDONLY);
	read(fd, buffer, 9);
	buffer[9] = '\0';
	number = 1;
	i = 0;
	while (i < 9)
	{
		number *= 10;
		number += (int)buffer[i++] % 10;
	}
	return (number);
}
