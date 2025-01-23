/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:12:23 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/23 11:19:38 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(void *param)
{
	(void)param;
	exit(0);
}

int	check_file(char *name)
{
	char	*extension;
	
	extension = ft_strchr(name, '.');
	if (ft_memcmp(extension, ".ber", 5) == 0)
		return (1);
	return (0);
}

char	**get_map(char *name)
{
	int	fd;
	char	*line;
	char	**map;
	char	*file;

	file = ft_strdup("");
	fd = open(name, O_RDWR);
	if (fd < 0)
	{
		printf("ERROR:\nInvalid file name!!");
		exit(0);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		file = ft_strjoin(file, line);
	}
	map = ft_split(file, '\n');
	return (map);
}


int main(int ac, char **av)
{
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
	game.player = mlx_xpm_file_to_image(game.mlx, "sprites/player_right.xpm", &game.img_width, &game.img_height);
	game.left_player = mlx_xpm_file_to_image(game.mlx, "sprites/player_left.xpm", &game.img_width, &game.img_height);
	game.right_player = mlx_xpm_file_to_image(game.mlx, "sprites/player_right.xpm", &game.img_width, &game.img_height);
	game.moves = mlx_xpm_file_to_image(game.mlx, "sprites/border.xpm", &width, &height);
	fill_holder(&game);
	load_frames(&game);
	(void)ac;
	
	game.count = 0;

	if (check_file(av[1]) == 0)
	{
		printf("ERROR:\nWrong file format!!");
		exit(0);
	}
	game.map = get_map(av[1]);
	if (map_manager(game.map, &data) == 0)
		exit(0);

	game.rows = 0;
	game.cols = strlen(game.map[0]);
	while (game.map[game.rows] != NULL)
		game.rows++;
	
	game.window = mlx_new_window(game.mlx, game.cols*game.img_width, game.rows*game.img_height + 80, "amongus");

	find_player(game.map, &game);
	if (path_manager(game.map, game.p_xpos, game.p_ypos) == 0)
	{
		printf("ERROR:\nExit not reachable!");
		exit(0);
	}
	
	initialize_enemies(&game);
	render_map(&game, game.map, game.img_width, game.img_width);
	mlx_hook(game.window, 2, 1L << 0, get_keycode, &game);
	mlx_loop_hook(game.mlx, loop, &game);
	mlx_hook(game.window, 17, 0, close_window, NULL);
	mlx_loop(game.mlx);

	return (0);
}
