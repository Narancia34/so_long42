/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:37:35 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/04 15:37:37 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

int	is_rectangular(char **map, t_data *data)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (i == 0)
			data->cols = strlen(map[i]);
		else if ((int)strlen(map[i]) != data->cols)
			return (0);
		data->rows++;
		i++;
	}
	return (1);
}

int	is_surrounded_bywalls(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			if ((i == 0 || i == data->rows - 1 || j == 0 \
			|| j == data->cols - 1) && map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_components(char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			if (map[i][j] == 'P')
				data->player++;
			else if (map[i][j] == 'E')
				data->exit++;
			else if (map[i][j] == 'C')
				data->collectibles++;
			else if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'X')
				return (printf("Error: extra obj"), 0);
			j++;
		}
		i++;
	}
	if (data->player != 1 || data->exit != 1 || data->collectibles < 1)
		return (0);
	return (1);
}

int	map_manager(char **map, t_data *data)
{
	data->rows = 0;
	data->cols = 0;
	data->player = 0;
	data->exit = 0;
	data->collectibles = 0;
	if (is_rectangular(map, data) == 0)
		return (printf("ERROR:\nmap is not rectangular"), 0);
	if (is_surrounded_bywalls(map, data) == 0)
		return (printf("Error: not surrounded by walls"), 0);
	if (check_map_components(map, data) == 0)
		return (printf("Error: extra player || exit || 0 collectible"), 0);
	return (1);
}
