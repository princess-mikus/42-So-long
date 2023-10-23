cmake_minimum_required(VERSION 3.26)
project(So_Long C)

set(CMAKE_C_STANDARD 90)

add_executable(So_Long main.c
        path_validation.c
        so_long.h
        list_control.c
        get_next_line.c
        get_next_line_utils.c
        ft_strdup.c
        ft_strlcpy.c
        ft_strlen.c)
