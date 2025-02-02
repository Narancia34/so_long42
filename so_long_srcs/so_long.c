/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:12:23 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/30 15:18:29 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_all(t_game *game)
{
	int	i;

	mlx_destroy_image(game->mlx, game->ground);
	mlx_destroy_image(game->mlx, game->wall);
	mlx_destroy_image(game->mlx, game->body);
	mlx_destroy_image(game->mlx, game->closedexit);
	mlx_destroy_image(game->mlx, game->left_player);
	mlx_destroy_image(game->mlx, game->right_player);
	mlx_destroy_image(game->mlx, game->moves);
	if (game->enemies)
		free(game->enemies);
	i = 0;
	while (i < 5)
	{
		mlx_destroy_image(game->mlx, game->frames[i]);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		mlx_destroy_image(game->mlx, game->digits[i]);
		i++;
	}
}

int	close_window(t_game *game)
{
	int	i;

	free_all(game);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	i = 0;
	if (game->map)
	{
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	free(game->mlx);
	exit(0);
}

void	init_texture(t_game *game)
{
	int	width;
	int	height;

	game->ground = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/floor.xpm", &game->img_width, &game->img_height);
	game->body = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/body.xpm", &game->img_width, &game->img_height);
	game->closedexit = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/closedexit.xpm", &game->img_width, &game->img_height);
	game->wall = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/crate.xpm", &game->img_width, &game->img_height);
	game->left_player = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/player_left.xpm", &game->img_width, &game->img_height);
	game->right_player = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/player_right.xpm", &game->img_width, &game->img_height);
	game->moves = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/border.xpm", &width, &height);
}

void	init_game(t_game *game, char *av)
{
	ft_memset(game, 0, sizeof(t_game));
	game->mlx = mlx_init();
	init_texture(game);
	game->flag = 0;
	game->keypress = 0;
	game->count = 0;
	fill_holder(game);
	load_frames(game);
	game->rows = 0;
	game->map = get_map(av, game);
	game->cols = strlen(game->map[0]);
	while (game->map[game->rows] != NULL)
		game->rows++;
	initialize_enemies(game);
	game->window = mlx_new_window(game->mlx, game->cols * game->img_width, \
	game->rows * game->img_height, "amongus");
}

int	main(int ac, char **av)
{
	t_game	game;
	t_data	data;

	if (ac == 2)
	{
		init_game(&game, av[1]);
		if (check_file(av[1]) == 0)
		{
			ft_printf("ERROR:\nWrong file format!!");
			close_window(&game);
		}
		find_player(game.map, &game);
		is_path_to_collect(game.map, &game);
		is_path_to_exit(game.map, &game);
		if (map_manager(game.map, &data) == 0)
			close_window(&game);
		render_map(&game, game.map, game.img_width, game.img_width);
		mlx_hook(game.window, 2, 1L << 0, get_keycode, &game);
		mlx_loop_hook(game.mlx, loop, &game);
		mlx_hook(game.window, 17, 0, close_window, &game);
		mlx_loop(game.mlx);
		close_window(&game);
	}
	return (0);
}
