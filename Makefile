NAME	:=	so_long
FILES	:=	main				\
			ft_strdup			\
			ft_strlen			\
			ft_strlcpy			\
			get_next_line		\
			get_next_line_utils	\
			list_control		\
			path_validation

CC		:=	gcc
OBJ_DIR	:=	obj
SRC		:=	$(addsuffix .c, $(FILES))
OBJ		:=	$(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	@$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@ 2>/dev/null

$(NAME): $(OBJ)
	@make -C ./mlx/ && mv ./mlx/libmlx.a . 2>/dev/null
	@$(CC) $(OBJ) -Lmlx -framework OpenGL -framework AppKit libmlx.a -o $(NAME) 2>/dev/null

clean:
	@rm -rf obj 2>/dev/null

fclean: clean
	@rm $(NAME) 2>/dev/null

re:	fclean all

.PHONY: all NAME clean fclean