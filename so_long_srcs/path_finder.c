/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:40:19 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/30 15:18:20 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(t_game *game, char **map_copy, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->rows || y >= game->cols)
		return ;
	if (map_copy[x][y] == '1' || map_copy[x][y] == '.' || map_copy[x][y] == 'X')
		return ;
	if (game->ignore_exit == 1 && map_copy[x][y] == 'E')
		return ;
	map_copy[x][y] = '.';
	flood_fill(game, map_copy, x + 1, y);
	flood_fill(game, map_copy, x - 1, y);
	flood_fill(game, map_copy, x, y + 1);
	flood_fill(game, map_copy, x, y - 1);
}

void	free_map_copy(char **map_copy, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

char	**copy_map(t_game *game, char **map)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(game->rows * sizeof(char *));
	if (!map_copy)
		exit(0);
	i = 0;
	while (i < game->rows)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			free_map_copy(map_copy, i);
			exit(0);
		}
		i++;
	}
	return (map_copy);
}

int	is_path_to_collect(char **map, t_game *game)
{
	char	**map_copy;
	int		x;
	int		y;

	game->ignore_exit = 1;
	map_copy = copy_map(game, map);
	flood_fill(game, map_copy, game->p_ypos, game->p_xpos);
	y = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < game->cols)
		{
			if (map[y][x] == 'C' && map_copy[y][x] != '.')
			{
				free_map_copy(map_copy, game->rows);
				ft_printf("ERROR:\nCan't get all collectibles");
				close_window(game);
			}
			x++;
		}
		y++;
	}
	free_map_copy(map_copy, game->rows);
	return (1);
}

int	is_path_to_exit(char **map, t_game *game)
{
	char	**map_copy;
	int		x;
	int		y;

	game->ignore_exit = 0;
	map_copy = copy_map(game, map);
	flood_fill(game, map_copy, game->p_ypos, game->p_xpos);
	y = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < game->cols)
		{
			if (map[y][x] == 'E' && map_copy[y][x] != '.')
			{
				free_map_copy(map_copy, game->rows);
				ft_printf("ERROR:\nCan't exit!");
				close_window(game);
			}
			x++;
		}
		y++;
	}
	free_map_copy(map_copy, game->rows);
	return (1);
}
