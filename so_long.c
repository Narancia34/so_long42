/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:12:23 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/28 11:48:46 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_game *game)
{
	int	i;

	mlx_destroy_image(game->mlx, game->ground);
	mlx_destroy_image(game->mlx, game->wall);
	mlx_destroy_image(game->mlx, game->body);
	mlx_destroy_image(game->mlx, game->closedexit);
	mlx_destroy_image(game->mlx, game->openexit);
	mlx_destroy_image(game->mlx, game->left_player);
	mlx_destroy_image(game->mlx, game->right_player);
	mlx_destroy_image(game->mlx, game->moves);
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
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	i = 0;
	if (game->map)
	{
		while (i < game->rows)
		{
			free(game->map[i]);
			i++;
		}
    	free(game->map);
	}
	free(game->mlx);
	exit(0);
}

int main(int ac, char **av)
{
	(void)ac;
	t_game game;
	t_data data;
	int width;
	int height;
	game.mlx = mlx_init();
	game.ground = mlx_xpm_file_to_image(game.mlx, "sprites/floor.xpm", &game.img_width, &game.img_height);
	game.body = mlx_xpm_file_to_image(game.mlx, "sprites/body.xpm", &game.img_width, &game.img_height);
	game.closedexit = mlx_xpm_file_to_image(game.mlx, "sprites/closedexit.xpm", &game.img_width, &game.img_height);
	game.openexit = mlx_xpm_file_to_image(game.mlx, "sprites/openexit.xpm", &game.img_width, &game.img_height);
	game.wall = mlx_xpm_file_to_image(game.mlx, "sprites/crate.xpm", &game.img_width, &game.img_height);
	game.left_player = mlx_xpm_file_to_image(game.mlx, "sprites/player_left.xpm", &game.img_width, &game.img_height);
	game.right_player = mlx_xpm_file_to_image(game.mlx, "sprites/player_right.xpm", &game.img_width, &game.img_height);
	game.moves = mlx_xpm_file_to_image(game.mlx, "sprites/border.xpm", &width, &height);
	game.flag = 0;
	game.keypress = 0;
	game.count = 0;

	
	fill_holder(&game);
	load_frames(&game);
	
	game.rows = 0;
	game.map = get_map(av[1], &game);
	game.cols = strlen(game.map[0]);
	while (game.map[game.rows] != NULL)
		game.rows++;
	
	initialize_enemies(&game);
	game.window = mlx_new_window(game.mlx, game.cols*game.img_width, game.rows*game.img_height + 80, "amongus");
	
	if (check_file(av[1]) == 0)
	{
		printf("ERROR:\nWrong file format!!");
		close_window(&game);
	}
	
	find_player(game.map, &game);
	
	if (!is_path_to_exit(game.map, game))
        printf("cant exit");
    if (!is_path_to_collect(game.map, game))
		printf("cant collect all");
	
	if (map_manager(game.map, &data) == 0)
		close_window(&game);

	render_map(&game, game.map, game.img_width, game.img_width);
	
	mlx_hook(game.window, 2, 1L << 0, get_keycode, &game);
	mlx_loop_hook(game.mlx, loop, &game);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_loop(game.mlx);

	return (0);
}
