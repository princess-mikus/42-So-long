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

$(MLX):
	@echo "Compiling MLX..."
	@make -C $(MLX_PATH) 1>/dev/null 2>/dev/null && cd $(MLX_PATH) && mv $(MLX) ../../$(MLX)
	@echo "MLX Compiled!"

$(LIBFT):
	@echo "Compiling LIBFT..."
	@make -C libft/ && mv libft/$(LIBFT) $(LIBFT) >/dev/null
	@echo "LIBFT Compiled!"

$(NAME): $(MLX) $(LIBFT) $(MOBJ) $(OBJ)
	@echo "Building executable..."
	@$(CC) $(MOBJ) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -g3 -o $(NAME) -fsanitize="address"
	@echo "Ready!"

bonus: $(MLX) $(LIBFT) $(BOBJ) $(OBJ)	
	@echo "Building bonus executable..."
	@$(CC) $(OBJ) $(BOBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -g3 -o $(NAME)
	@echo "Ready!"

clean:
	@rm -rf $(OBJ_DIR) 	>/dev/null
	@rm -f $(LIBFT)		>/dev/null
	@make -C libft/ clean >/dev/null
	@make -C $(MLX_PATH) clean >/dev/null
	@echo "Clean!\n"

fclean: clean
	@rm -f $(MLX)	>/dev/null
	@rm -f $(NAME)	>/dev/null
	@make -C libft/ fclean >/dev/null

re:	fclean all

.PHONY: all NAME clean fclean bonus