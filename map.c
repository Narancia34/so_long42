#include <mlx.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>

// typedef struct s_game {
// 	void	*mlx;
// 	void	*ground;
// 	void	*wall;
// 	void	*player;
// 	void	*vent;
// 	void	*window;
// 	char	**map;
// 	int		p_xpos;
// 	int		p_ypos;
// 	int		img_width;
// 	int		img_height;
// 	int		count;
// } t_game;

// int check_map(char **map)
// {
// 	int rows = 0;
// 	int cols = 0;
// 	int player_spos = 0;
// 	int exit = 0;
// 	int collectible = 0;
// 	int i = 0;
// 	int j = 0;

// 	while (map[i])
// 	{
// 		if (i == 0)
// 			cols = strlen(map[i]);
// 		else if ((int)strlen(map[i]) != cols)
// 			return (printf("Error: Map is not rectangular\n"), 0);
// 		rows++;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < rows)
// 	{
// 		while (j < cols)
// 		{
// 			if ((i == 0 || i == rows - 1 || j == 0 || j == cols - 1) && map[i][j] != '1')
// 				return (printf("Error: not surrounded by walls"), 0);
// 			if (map[i][j] == 'P')
// 				player_spos++;
// 			else if (map[i][j] == 'E')
// 				exit++;
// 			else if (map[i][j] == 'C')
// 				collectible++;
// 			else if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'X')
// 				return (printf("Error: extra obj"), 0);
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// 	if (player_spos != 1 || exit != 1 || collectible < 1)
// 		return (printf("Error: extra player || exit || 0 collectible"), 0);
// 	return (1);

// }

// int find_path(char **map, int x_pos, int y_pos, char target, char check)
// {

// 	if (map[x_pos][y_pos] == check || map[x_pos][y_pos] == '1' || map[x_pos][y_pos] == 'X')
// 		return (0);
// 	if (map[x_pos][y_pos] == 'E')
// 		return (1);
// 	map[x_pos][y_pos] = check;
// 	if (find_path(map, x_pos + 1, y_pos, target, check)) // south
// 		return (1); 
// 	if (find_path(map, x_pos - 1, y_pos, target, check)) // north
// 		return (1); 
// 	if (find_path(map, x_pos, y_pos + 1, target, check)) // east
// 		return (1); 
// 	if (find_path(map, x_pos, y_pos - 1, target, check)) // west
// 		return (1);
// 	return (0);
// }


// void	draw_tile(t_game *game, int x, int y, int color, int img_width, int img_height)
// {
// 	int	i;
// 	int	j;

// 	for (i = 0; i < img_height; i++) {
// 		for (j = 0; j < img_width; j++) {
// 			mlx_pixel_put(game->mlx, game->window, x * img_width + j, y * img_height + i, color);
// 		}
// 	}
// }

// void	render_map(t_game *game, char **map, int img_width, int img_height)
// {
// 	int		i;
// 	int		j;
// 	char	*count;

// 	for (i = 0; map[i]; i++) {
// 		for (j = 0; map[i][j]; j++) {
// 			int xpos = j * img_width;
// 			int ypos = i * img_height;
// 			if (map[i][j] == '1')
// 				mlx_put_image_to_window(game->mlx, game->window, game->wall, xpos, ypos);
// 			else if (map[i][j] == '0')
// 				mlx_put_image_to_window(game->mlx, game->window, game->ground, xpos, ypos);
// 			else if (map[i][j] == 'C')
// 				mlx_put_image_to_window(game->mlx, game->window, game->vent, xpos, ypos);
// 			else if (map[i][j] == 'E')
// 				draw_tile(game, j, i, 0xFF0000, img_width, img_height); // Red for exit
// 			else if (map[i][j] == 'X')
// 				draw_tile(game, j, i, 0xFFFF00, img_width, img_height); // yellow for enemy
// 			else if (map[i][j] == 'P')
// 			{
// 				// mlx_put_image_to_window(game->mlx, game->window, game->ground, xpos, ypos);
// 				mlx_put_image_to_window(game->mlx, game->window, game->player, xpos, ypos);
// 			}
// 		}
// 	}
// 	count = ft_itoa(game->count);
// 	mlx_string_put(game->mlx, game->window, 20, 20, 0xFFFF00, count);
// }

// void find_player(char **map, t_game *game)
// {
// 	int i = 0;
// 	int j;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while(map[i][j])
// 		{
// 			if (map[i][j] == 'P')
// 			{
// 				game->p_xpos = j;
// 				game->p_ypos = i;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }


// int key_press(int keycode, t_game *game)
// {
// 	int		j;
// 	int		i;
// 	int		n_ypos;
// 	int		n_xpos;
// 	char	*gamover_path;
// 	void	*gameover;

// 	gamover_path = "/home/mgamraou/Downloads/gettyimages-1325433246-640x640.xpm";
// 	gameover = mlx_xpm_file_to_image(game->mlx, gamover_path, &i, &j);
// 	n_xpos = game->p_xpos;
// 	n_ypos = game->p_ypos;
// 	if (keycode == ESC_KEY)
// 		exit(0);
// 	if (keycode == 'w')
// 		n_ypos--;
// 	else if (keycode == 's')
// 		n_ypos++;
// 	else if (keycode == 'a')
// 		n_xpos--;
// 	else if (keycode == 'd')
// 		n_xpos++;
// 	if (game->map[n_ypos][n_xpos] == '1')
// 		return (1);
// 	else if (game->map[n_ypos][n_xpos] == 'X')
// 	{
// 		mlx_clear_window(game->mlx, game->window);
// 		mlx_put_image_to_window(game->mlx, game->window, gameover, 0, 0);
// 	}
// 	else if (game->map[n_ypos][n_xpos] == 'E')
// 	{
// 		i = 0;
// 		while (game->map[i])
// 		{
// 			j = 0;
// 			while (game->map[i][j])
// 			{
// 				if (game->map[i][j] == 'C')
// 					return (1);
// 				j++;
// 			}
// 			i++;
// 		}
// 		mlx_clear_window(game->mlx, game->window);
// 		mlx_put_image_to_window(game->mlx, game->window, gameover, 0, 0);
// 	}
// 	else
// 	{
// 		game->map[game->p_ypos][game->p_xpos] = '0';
// 		game->map[n_ypos][n_xpos] = 'P';
// 		game->count++;
// 		mlx_clear_window(game->mlx, game->window);
// 		render_map(game, game->map, game->img_width, game->img_width);
// 		game->p_xpos = n_xpos;
// 		game->p_ypos = n_ypos;
// 	}
// }

int	close_window(void *param)
{
	(void)param;
	exit(0);
}

int	check_file(char *name)
{
	char	*extension;
	int		i;

	i = 0;
	extension = ft_strchr(name, '.');
	while (extension[i])
	{
		
	}
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
	// char *map[] = {
	// 	"1111111111111111111111111111111111",
	// 	"1000000100000000010000100001000001",
	// 	"1000000000000001010000000011000011",
	// 	"1000000000000001001010000000000001",
	// 	"1000010100001100000000100010010001",
	// 	"1000000001000000000000000000000001",
	// 	"1010000100000000000000000000100011",
	// 	"1000000000000000000000000000100001",
	// 	"1010000000000000000010000000000001",
	// 	"1010100000000001000010000010000111",
	// 	"1000000000010001000010100010000001",
	// 	"1000000000000000000000000000000101",
	// 	"1000100100010101000000000P00010001",
	// 	"10000000000000000000C0E00001000001",
	// 	"1000000000000100000000000001000001",
	// 	"1111111111111111111111111111111111",
	// 	NULL
	// };

	t_game game;
	t_data data;
	char	*ground_path = "/home/mgamraou/Downloads/floor_1_.xpm";
	char	*wall_path = "/home/mgamraou/Downloads/crate-1.xpm";
	char    *palyer_path = "/home/mgamraou/Downloads/player_1_.xpm";
	char	*vent_path = "/home/mgamraou/Downloads/ventsus-1.xpm";
	char	*exit_path = "/home/mgamraou/Downloads/exit-1.xpm";
	//char	**map = get_map(av[1]);
	
	game.mlx = mlx_init();
	game.map = get_map(av[1]);
	game.ground = mlx_xpm_file_to_image(game.mlx, ground_path, &game.img_width, &game.img_height);
	game.vent = mlx_xpm_file_to_image(game.mlx, vent_path, &game.img_width, &game.img_height);
	game.exit = mlx_xpm_file_to_image(game.mlx, exit_path, &game.img_width, &game.img_height);
	game.wall = mlx_xpm_file_to_image(game.mlx, wall_path, &game.img_width, &game.img_height);
	game.player = mlx_xpm_file_to_image(game.mlx, palyer_path, &game.img_width, &game.img_height);
	//game.window = mlx_new_window(game.mlx, 2000, 2000, "2D Game Map");
	game.count = 0;

	
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

	//render_map(&game, game.map, game.img_width, game.img_height);

	mlx_key_hook(game.window, key_press, &game);
	mlx_hook(game.window, 17, 0, close_window, NULL);

	mlx_loop(game.mlx);

	return (0);
}
