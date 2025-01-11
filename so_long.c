/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:12:23 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/11 17:02:27 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "get_next_line.h"
#include "libft.h"
#include "so_long.h"
#include <fcntl.h>

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
	char	*vent_path = "/home/mgamraou/Downloads/ventsus-1.xpm";
	char	*exit_path = "/home/mgamraou/Downloads/exit-1.xpm";
	
	game.mlx = mlx_init();
	game.ground = mlx_xpm_file_to_image(game.mlx, ground_path, &game.img_width, &game.img_height);
	game.vent = mlx_xpm_file_to_image(game.mlx, vent_path, &game.img_width, &game.img_height);
	game.exit = mlx_xpm_file_to_image(game.mlx, exit_path, &game.img_width, &game.img_height);
	game.wall = mlx_xpm_file_to_image(game.mlx, wall_path, &game.img_width, &game.img_height);
	game.player = mlx_xpm_file_to_image(game.mlx, player_path, &game.img_width, &game.img_height);
	game.count = 0;

	if (check_file(av[1]) == 0)
	{
		printf("ERROR:\nWrong file format!!");
		exit(0);
	}
	game.map = get_map(av[1]);
	if (map_manager(game.map, &data) == 0)
		exit(0);

	int rows = 0;
	int cols = strlen(game.map[0]);
	while (game.map[rows] != NULL)
		rows++;
	
	game.window = mlx_new_window(game.mlx, cols*game.img_width, rows*game.img_height, "amongus");
	
	char **map_copy = malloc(rows * sizeof(char *));
	for (int i = 0; i < rows; i++)
	{
		map_copy[i] = strdup(game.map[i]);
	}

	find_player(game.map, &game);
	if (find_path(map_copy, game.p_ypos, game.p_xpos, '0') == 0)
		exit(0);
	for (int i = 0; i < rows; i++)
	{
		free(map_copy[i]);
	}
	free(map_copy);
	
	//render_map(&game, game.map, game.img_width, game.img_width);
	mlx_hook(game.window, 2, 1L << 0, key_press, &game); 
	mlx_hook(game.window, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	// mlx_hook(game.window, 2, 1L << 0, get_keycode, &game);
	// mlx_loop_hook(game.mlx, handle_keypress, &game);
	// mlx_key_hook(game.window, key_press, &game);
	// mlx_loop_hook(game.mlx, animation, &game);
	mlx_hook(game.window, 17, 0, close_window, NULL);
	mlx_loop(game.mlx);

	return (0);
}

// what is left to do :
// animation
// movement on hold key
// maybe enhance player movement
// maybe display counter with textures


// for animation ill just make enemies as spikes that appear and dissappear and so on