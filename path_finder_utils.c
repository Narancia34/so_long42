/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:56:53 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/23 10:31:24 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(char **map, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				game->p_xpos = j;
				game->p_ypos = i;
			}
			j++;
		}
		i++;
	}
}

int	count_collectibles(char **map)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

char	**copy_map(char **map)
{
	int		rows;
	int		i;
	char	**map_copy;

	rows = 0;
	i = 0;
	while (map[rows])
		rows++;
	map_copy = malloc(rows * sizeof(char *));
	while (i < rows)
	{
		map_copy[i] = ft_strdup(map[i]);
		i++;
	}
	return (map_copy);
}

void	free_copy(char **map)
{
	int	rows;
	int	i;

	rows = 0;
	i = 0;
	while (map[rows])
		rows++;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	is_valid_move(char **map, int x, int y)
{
	int	rows;
	int	cols;

	rows = 0;
	while (map[rows])
		rows++;
	cols = ft_strlen(map[0]);
	return (x >= 0 && x < rows && y >= 0 && y < cols && \
	map[x][y] != '1' && map[x][y] != '2');
}
