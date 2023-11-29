cmake_minimum_required(VERSION 3.26)
project(So_Long C)

set(CMAKE_C_STANDARD 90)

add_executable(So_Long main.c
        path_validation.c
        so_long.h
        list_control.c
        libft/get_next_line.c
        libft/get_next_line_utils.c
        libft/ft_strdup.c
        libft/ft_strlcpy.c
        libft/ft_strlen.c map_modification.c)
