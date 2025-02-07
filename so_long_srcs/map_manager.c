/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:37:35 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/30 15:17:55 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	handdle_error(t_data data)
{
	if (data.player > 1)
		return (ft_printf("Error:\nExtra starting position\n"), 0);
	else if (data.player == 0)
		return (ft_printf("Error:\nNo starting position\n"), 0);
	if (data.exit > 1)
		return (ft_printf("Error:\nExtra exit\n"), 0);
	else if (data.exit == 0)
		return (ft_printf("Error:\nNo exit\n"), 0);
	if (data.collectibles < 1)
		return (ft_printf("Error:\nNo collectibles"), 0);
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
				return (ft_printf("Error:\nExtra obj"), 0);
			j++;
		}
		i++;
	}
	if (handdle_error(*data) == 0)
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
		return (ft_printf("ERROR:\nMap is not rectangular"), 0);
	if (is_surrounded_bywalls(map, data) == 0)
		return (ft_printf("Error:\nNot surrounded by walls"), 0);
	if (check_map_components(map, data) == 0)
		return (0);
	return (1);
}
