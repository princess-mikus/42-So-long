NAME	:=	so_long
MLX		:=	libmlx.a
LIBFT	:=	libft.a
FILES	:=	so_long				\
			list_control		\
			path_validation		\
			movement			\
			map_validation		\
			map_updates			\
			exit				\
			utils				\
			map_import			\
			walls
BFILES	:=	so_long

CC		:=	gcc
OBJ_DIR	:=	obj
SRC		:=	$(addsuffix .c, $(FILES))
BSRC	:=	$(addsuffix _bonus.c, $(BFILES))
OBJ		:=	$(SRC:%.c=$(OBJ_DIR)/%.o)
BOBJ	:=	$(BSRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	@$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@ 2>/dev/null

$(LIBFT):
	@echo "Compiling LIBFT..."
	@make -C libft/ && mv libft/$(LIBFT) $(LIBFT) >/dev/null
	@echo "LIBFT Compiled!"

$(NAME): $(LIBFT) $(OBJ)
	@echo "Compiling MLX..."
	@make -C ./mlx/ 1>/dev/null 2>/dev/null && mv ./mlx/libmlx.a . 2>/dev/null
	@echo "Compiled!"
	@echo "Making executable..."
	@$(CC) $(OBJ) -Lmlx -framework OpenGL -framework AppKit $(MLX) $(LIBFT) -o $(NAME) -g -fsanitize=address 2>/dev/null
	@echo "Ready!"

bonus: $(BOJB) $(LIBFT) $(BOBJ) $(OBJ)
	@echo "Compiling MLX..."
	@make -C ./mlx/ 1>/dev/null 2>/dev/null && mv ./mlx/libmlx.a . 2>/dev/null
	@echo "Compiled!"
	@echo "Making bonus executable..."
	@rm $(OBJ_DIR)/so_long.o >/dev/null
	@$(CC) $(OBJ) $(BOBJ) -Lmlx -framework OpenGL -framework AppKit $(MLX) $(LIBFT) -o $(NAME) -g -fsanitize=address
	@echo "Ready!"


clean:
	@rm -rf obj >/dev/null
	@rm $(LIBFT) 2>/dev/null
	@make -C libft/ clean
	@echo "Cleaned\n"

fclean: clean
	@rm $(NAME) >/dev/null
	@rm $(MLX)	>/dev/null
	@make -C libft/ fclean >/dev/null

re:	fclean all

.PHONY: all NAME clean fclean bonus