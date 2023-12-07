/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcasaubo <fcasaubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:03:16 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/07 15:39:12 by fcasaubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Micaela Casaubon on 9/7/23.
//

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/get_next_line.h"
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "mlx/mlx.h"
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <errno.h>

// Main struct
typedef struct s_data
{
	int		movements;
	char	**map;
	int		map_y;
	int		map_x;
	int		coins;
	int		exit;
	int		player_x;
	int		player_y;
}		t_data;

// Validator lists
typedef struct s_list
{
	int		y;
	int		x;
	void	*next;
}		t_list;

// MLX data structure (Sprite images)

typedef struct s_images
{
	void	*wall;
	void	*left_corner;
	void	*right_corner;
	void	*middle_corner;
	void	*upper_left_corner;
	void	*upper_right_corner;
	void	*upper_middle_corner;
	void	*left_wall;
	void	*right_wall;
	void	*player;
	void	*door_open;
	void	*door_closed;
	void	*coins;
	void	*floor;
}		t_images;

// Mlx Window structure

typedef struct s_window
{
	int		size_x;
	int		size_y;
	void	*mlx;
	void	*ptr;
	void	*background;
	int		bg_x;
	int		bg_y;
}	t_window;

// Simple map validation
int		map_validator(t_data *data);
int		duplicate_validator(t_data *data);
int		wall_validator(char **map);

// Map playability validation
void	search_exit(t_data *data, char **map, t_list **positions);
int		path_validator(t_data *data);

// List Control
t_list	*sl_lstnew(int y, int x);
void	sl_lstadd_front(t_list **lst, t_list *new);
void	sl_lstadd_back(t_list **lst, t_list *new);
int		key_hook(int keycode, void **temp);
void	update_map(t_window *win, t_data *data, t_images *images);

#endif //SO_LONG_H
