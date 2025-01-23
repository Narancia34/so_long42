/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:10:52 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/23 10:31:55 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

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

int	check_collectibles(char **map, int x_pos, \
int y_pos, int *collectibles_found)
{
	if (!is_valid_move(map, x_pos, y_pos))
		return (0);
	if (map[x_pos][y_pos] == 'C')
		(*collectibles_found)++;
	map[x_pos][y_pos] = '2';
	check_collectibles(map, x_pos + 1, y_pos, collectibles_found);
	check_collectibles(map, x_pos - 1, y_pos, collectibles_found);
	check_collectibles(map, x_pos, y_pos + 1, collectibles_found);
	check_collectibles(map, x_pos, y_pos - 1, collectibles_found);
	return (1);
}

int	path_manager(char **map, int x_pos, int y_pos)
{
	int		total_collectibles;
	int		collectibles_found;
	int		check_exit;
	char	**map_copy;

	total_collectibles = count_collectibles(map);
	collectibles_found = 0;
	map_copy = copy_map(map);
	check_collectibles(map_copy, x_pos, y_pos, &collectibles_found);
	free(map_copy);
	map_copy = copy_map(map);
	check_exit = find_path(map_copy, x_pos, y_pos, '0');
	free(map_copy);
	return (collectibles_found == total_collectibles && check_exit);
}
