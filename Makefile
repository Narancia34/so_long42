CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long.a
FLAGS = -lmlx -lX11 -lXext -lm
NAME_PROGRAMME = so_long
SRCS = so_long.c map_manager.c path_finder.c render_map.c manage_mvt.c get_next_line.c get_next_line_utils.c put_count.c handle_enemy.c path_finder_utils.c
OFILES = $(SRCS:.c=.o)

all: $(NAME_PROGRAMME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

$(NAME_PROGRAMME): $(NAME)
	$(CC) $(CFLAGS) $(OFILES) libft.a -o $(NAME_PROGRAMME) $(FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -rf $(NAME) $(NAME_PROGRAMME)

re: fclean all

.PHONY: clean fclean re
.SECONDARY: $(OFILES)
