/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 13:17:01 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/03 09:20:34 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

typedef struct s_data {
	int rows;
	int cols;
	int exit;
	int player;
	int collectibles;
} t_data;


int is_rectangular(char **map, t_data *data)
{
	int i;

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

int is_surrounded_bywalls(char **map, t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			if ((i == 0 || i == data->rows - 1 || j == 0 || j == data->cols - 1) && map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int check_map_components(char **map, t_data *data)
{
	int i;
	int j;

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
			else if (map[i][j] != '0' && map[i][j] != '1')
				return (printf("Error: extra obj"), 0);
			j++;
		}
		i++;
	}
	if (data->player != 1 || data->exit != 1 || data->collectibles < 1)
		return (0);
	return (1);    
}

int map_manager(char **map, t_data *data)
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
int main ()
{
	char *map[] = {
		"1111111111111111111111111111111111",
		"1P100001C0000000010C00100001000C01",
		"1C00010111111001010000111011000011",
		"1011110100001001C1C00C001110001001",
		"100001010000110001110110001C011001",
		"1C111100010000C0010C0100001111C001",
		"101000010111111111000100100C100011",
		"10111C0100000000010001011000101001",
		"1010CC01111111110110110100111010C1",
		"1C10100000000001001010010010001111",
		"1011111100010001001010110010000001",
		"1000C00111110101000010C11111110101",
		"1C0010010C01C101011111111C0001C001",
		"11111001100101011100C0E00001000001",
		"100C0000C0000100000110001001001CC1",
		"1111111111111111111111111111111111",
		NULL
	};
	t_data data;
	map_manager(map, &data);

}
