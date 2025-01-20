/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:12:23 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/20 10:09:36 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include "so_long.h"

int	close_window(void *param)
{
	(void)param;
	exit(0);
}

int	check_file(char *name)
{
	char	*extension;
	int		i;
	
	extension = ft_strchr(name, '.');
	if (ft_memcmp(extension, ".ber", 5) == 0)
		return (1);
	return (0);
}

char	**get_map(char *name)
{
	int	fd;
	int i;
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
	t_keys	keys = {0,0,0,0};
	char	*ground_path = "/home/mgamraou/Downloads/floor_1_.xpm";
	char	*wall_path = "/home/mgamraou/Downloads/crate-1.xpm";
	char    *player_path = "/home/mgamraou/Downloads/player_1_.xpm";
	char	*vent_path = "/home/mgamraou/Downloads/vertopal.com_susbody-1.xpm";
	char	*exit_path = "/home/mgamraou/Downloads/exit-1.xpm";
	char	*player_right = "/home/mgamraou/Downloads/player_1_.xpm";
	char	*player_left = "/home/mgamraou/Downloads/player_left.xpm";
	
	game.mlx = mlx_init();
	game.ground = mlx_xpm_file_to_image(game.mlx, ground_path, &game.img_width, &game.img_height);
	game.vent = mlx_xpm_file_to_image(game.mlx, vent_path, &game.img_width, &game.img_height);
	game.exit = mlx_xpm_file_to_image(game.mlx, exit_path, &game.img_width, &game.img_height);
	game.wall = mlx_xpm_file_to_image(game.mlx, wall_path, &game.img_width, &game.img_height);
	game.player = mlx_xpm_file_to_image(game.mlx, player_path, &game.img_width, &game.img_height);
	game.left_player = mlx_xpm_file_to_image(game.mlx, player_left, &game.img_width, &game.img_height);
	game.right_player = mlx_xpm_file_to_image(game.mlx, player_right, &game.img_width, &game.img_height);
	fill_holder(&game);
	load_frames(&game);
	
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
	
	game.window = mlx_new_window(game.mlx, game.cols*game.img_width, game.rows*game.img_height + 100, "amongus");

	
	char **map_copy = malloc(game.rows * sizeof(char *));
	for (int i = 0; i < game.rows; i++)
	{
		map_copy[i] = strdup(game.map[i]);
	}

	find_player(game.map, &game);
	if (find_path(map_copy, game.p_ypos, game.p_xpos, '0') == 0)
		exit(0);
	for (int i = 0; i < game.rows; i++)
	{
		free(map_copy[i]);
	}
	free(map_copy);
	
	render_map(&game, game.map, game.img_width, game.img_width);
	mlx_hook(game.window, 2, 1L << 0, get_keycode, &game);
	mlx_loop_hook(game.mlx, loop, &game);
	mlx_hook(game.window, 17, 0, close_window, NULL);
	mlx_loop(game.mlx);

	return (0);
}
