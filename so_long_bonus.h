/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikus <mikus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:39:59 by fcasaubo          #+#    #+#             */
/*   Updated: 2023/12/27 19:26:56 by mikus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "libft/get_next_line.h"
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "mlx/mlx_mac/mlx.h"
# include <time.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

# define ENEMY_RATE	16
# define JUMP_CHANCE 20
# define MOVEMENT_CHANCE 95
# define TICK_RATE 100

// Main struct
typedef struct s_data
{
	int		players;
	int		movements;
	char	**map;
	int		map_y;
	int		map_x;
	int		coins;
	int		exit;
	int		player_x;
	int		player_y;
	int		enemy_count;
	int		tick;
	int		random_fd;
}		t_data;

typedef struct s_temp_list
{
	char	*line;
	void	*next;
}		t_temp_list;

// Validator lists
typedef struct s_list
{
	int		y;
	int		x;
	void	*next;
}		t_list;

// Enemy images
typedef struct s_enemy
{
	void	*enemy_jumping;
}	t_enemy;

// MLX images structure (Sprite images)

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
	void	*coins_taken;
	void	*floor;
	void	*enemy;
	void	*number[10];
	void	*black;
	void	*player_dead[2];
	void	*game_over;
	t_enemy	enemy_images;
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

// Import map to structure
void	import_map(t_data *data, int fd);

// Simple map validation
int		map_validator(t_data *data);

// Map playability validation
int		path_validator(t_data *data);

// List Control
t_list	*sl_lstnew(int y, int x);
void	sl_lstadd_front(t_list **lst, t_list *new);
void	sl_lstadd_back(t_list **lst, t_list *new);

// Function hooked to key events
int		key_hook(int keycode, void **temp);

// Wall drawing
void	draw_outter_walls(t_window *win, t_data *data, t_images *images);
// Wall Drawing
void	draw_inner_walls(t_window *win, t_data *data, t_images *images);

// Replacing mlx_put_image 'cause it's too long for Normie
void	put_image(t_window	*win, void	*img, int x, int y);

// Put step count in upper right corner of the screen
void	put_number(int nbr, t_window *win, t_data *data, t_images *images);

// Map Drawing
void	update_map(t_window *win, t_data *data, t_images *images);

// Check if player won, then proceeds to free everything
void	check_win(t_window *win, t_data *data, t_images *images);

// Utils
void	free_array(void **array);

// Close program cleanly
void	close_game(t_window *win, t_data *data, t_images *images);

// Spawn enemies
void	spawn_enemies(t_data *data);

// Init enemies
void	init_enemies(t_window *window, t_images *images);

// Move enemies
void	enemy_movement(t_data *data, int enemy_x, int enemy_y);

// Function hooked to the loop execution
int		loop_hook(void **structures);

// Random Number Generator, 'cause Rand() sucks
int		get_random_number(void);

#endif //SO_LONG_H