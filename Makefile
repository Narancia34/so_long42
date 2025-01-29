CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -lmlx -lX11 -lXext -lm

NAME = so_long

SRCS = so_long.c map_manager.c render_map.c manage_mvt.c get_next_line.c \
       get_next_line_utils.c put_count.c handle_enemy.c path_finder.c utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) ./libft/libft.a -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re