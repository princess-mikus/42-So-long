NAME	:=	so_long
OS 		:= $(shell uname)
MLX		:=	libmlx.a
LIBFT	:=	libft.a
FILES	:=	list_control		\
			path_validation		\
			map_validation		\
			exit				\
			utils				\
			map_import			\
			walls

MFILES	:=	so_long				\
			movement			\
			map_updates

BFILES	:=	enemies				\
			loop_hook			\
			enemy_movement		\
			random				\
			counter

CC		:=	gcc
OBJ_DIR	:=	obj
SRC		:=	$(addsuffix .c, $(FILES))
MSRC	:=	$(addsuffix .c, $(MFILES))
BSRC	:=	$(addsuffix _bonus.c, $(MFILES) $(BFILES))
OBJ		:=	$(SRC:%.c=$(OBJ_DIR)/%.o)
BOBJ	:=	$(BSRC:%.c=$(OBJ_DIR)/%.o)
MOBJ	:=	$(MSRC:%.c=$(OBJ_DIR)/%.o)
MBOBJ	:=	$(MBSRC:%.c=$(OBJ_DIR)/%.o)

ifeq ($(OS), Darwin)
MLX_PATH	= mlx/mlx_mac
MLX_FLAGS	= -framework OpenGL -framework AppKit
else ifeq ($(OS), Linux)
MLX_PATH	= mlx/mlx_linux
MLX_FLAGS	= -L/usr/lib -lXext -lX11 -lm -lz
endif

all: $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	@$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(LIBFT):
	@echo "Compiling LIBFT..."
	@make -C libft/ && mv libft/$(LIBFT) $(LIBFT) >/dev/null
	@echo "LIBFT Compiled!"

$(NAME): $(LIBFT) $(MOBJ) $(OBJ)
	@echo "Compiling MLX..."
	@make -C $(MLX_PATH) 1>/dev/null 2>/dev/null && cd $(MLX_PATH) && mv $(MLX) ../../$(MLX)
	@echo "Compiled!"
	@echo "Making executable..."
	$(CC) $(MOBJ) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "Ready!"

bonus: $(BOJB) $(LIBFT) $(BOBJ) $(OBJ)	
	@echo "Compiling MLX..."
	@make -C $(MLX_PATH) 1>/dev/null 2>/dev/null && cd $(MLX_PATH) && mv $(MLX) ../../$(MLX)
	@echo "Compiled!"
	@echo "Making bonus executable..."
	@$(CC) $(OBJ) $(BOBJ) $(LIBFT)  $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "Ready!"

clean:
	@rm -rf obj >/dev/null
	@rm $(LIBFT) 2>/dev/null
	@make -C libft/ clean
	@make $(MLX_PATH) clean
	@echo "Cleaned\n"

fclean: clean
	@rm $(MLX)	>/dev/null
	@rm $(NAME) >/dev/null
	@make -C libft/ fclean >/dev/null

re:	fclean all

.PHONY: all NAME clean fclean bonus