NAME	:=	so_long
MLX		:=	libmlx.a
LIBFT	:=	libft.a
FILES	:=	main				\
			list_control		\
			path_validation		\
			movement

CC		:=	gcc
OBJ_DIR	:=	obj
SRC		:=	$(addsuffix .c, $(FILES))
OBJ		:=	$(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	@$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@ 2>/dev/null

$(LIBFT):
	@make -C libft/ && mv libft/$(LIBFT) $(LIBFT)

$(NAME): $(LIBFT) $(OBJ)
	@make -C ./mlx/ 1>/dev/null 2>/dev/null && mv ./mlx/libmlx.a . 2>/dev/null
	@$(CC) $(OBJ) -Lmlx -framework OpenGL -framework AppKit $(MLX) $(LIBFT) -o $(NAME) -g -fsanitize=address 2>/dev/null

clean:
	@rm -rf obj 2>/dev/null
	@rm $(LIBFT) 2>/dev/null
	@make -C libft/ clean

fclean: clean
	@rm $(NAME) 2>/dev/null
	@make -C libft/ fclean

re:	fclean all

.PHONY: all NAME clean fclean