/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:10:52 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/08 10:11:03 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

int	find_path(char **map, int x_pos, int y_pos, char target)
{
	if (map[x_pos][y_pos] == '2' || map[x_pos][y_pos] == '1' \
	|| map[x_pos][y_pos] == 'X')
		return (0);
	if (map[x_pos][y_pos] == 'E')
		return (1);
	map[x_pos][y_pos] = '2';
	if (find_path(map, x_pos + 1, y_pos, target))
		return (1);
	if (find_path(map, x_pos - 1, y_pos, target))
		return (1);
	if (find_path(map, x_pos, y_pos + 1, target))
		return (1);
	if (find_path(map, x_pos, y_pos - 1, target))
		return (1);
	return (0);
}
