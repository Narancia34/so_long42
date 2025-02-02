/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:09:40 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/30 15:18:47 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_file(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + (len - 4), ".ber", 4) != 0)
		return (0);
	return (1);
}

char	*read_map(int fd)
{
	char	*file;
	char	*temp;
	char	*line;

	file = ft_strdup("");
	if (fd < 0)
	{
		free(file);
		ft_printf("ERROR:\nInvalid file name!!");
		return (NULL);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = file;
		file = ft_strjoin(file, line);
		free(temp);
		free(line);
	}
	return (file);
}

char	**get_map(char *name, t_game *game)
{
	int		fd;
	char	*file;
	char	**map;

	fd = open(name, O_RDWR);
	if (fd < 0)
	{
		ft_printf("ERROR:\nCannot open file!");
		close_window(game);
	}
	file = read_map(fd);
	if (!file)
		close_window(game);
	map = ft_split(file, '\n');
	free(file);
	close(fd);
	return (map);
}

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
