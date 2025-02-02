CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -lmlx -lX11 -lXext -lm

NAME = so_long

SRCS = ./so_long_srcs/so_long.c ./so_long_srcs/map_manager.c ./so_long_srcs/render_map.c ./so_long_srcs/manage_mvt.c ./so_long_srcs/get_next_line.c \
       ./so_long_srcs/get_next_line_utils.c ./so_long_srcs/put_count.c ./so_long_srcs/handle_enemy.c ./so_long_srcs/path_finder.c ./so_long_srcs/utils.c \
	   ./so_long_srcs/ft_split.c ./so_long_srcs/libft_utils.c ./so_long_srcs/libft_utils2.c \
	   ./ft_printf/ft_printf.c  ./ft_printf/ft_putchar.c ./ft_printf/ft_puthexa.c ./ft_printf/ft_putnbr.c ./ft_printf/ft_putstr.c ./ft_printf/ft_putunint.c ./ft_printf/ft_putaddress.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re