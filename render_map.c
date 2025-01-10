/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:26:21 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/09 19:07:57 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <mlx.h>

void	spikes_animation(t_game *game, int xpos, int ypos)
{
	static int i;
	if (i == 0)
	{
		mlx_put_image_to_window(game->mlx, game->window, game->vent, xpos, ypos);
		i = 1;
	}
	else if (i == 1)
	{
		mlx_put_image_to_window(game->mlx, game->window, game->wall, xpos, ypos);
		i = 0;
	}
}

void	put_image(char c, t_game *game, int xpos, int ypos)
{
	if (c == '1')
		mlx_put_image_to_window(game->mlx, \
		game->window, game->wall, xpos, ypos);
	else if (c == '0')
		mlx_put_image_to_window(game->mlx, \
		game->window, game->ground, xpos, ypos);
	else if (c == 'C')
		mlx_put_image_to_window(game->mlx, \
		game->window, game->vent, xpos, ypos);
	else if (c == 'E')
		mlx_put_image_to_window(game->mlx, \
		game->window, game->exit, xpos, ypos);
	else if (c == 'X')
		mlx_put_image_to_window(game->mlx, game->vent, game->vent, xpos, ypos);
	else if (c == 'P')
		mlx_put_image_to_window(game->mlx, \
		game->window, game->player, xpos, ypos);
}

void	render_map(t_game *game, char **map, int img_width, int img_height)
{
	int		i;
	int		j;
	int		xpos;
	int		ypos;
	char	*count;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			xpos = j * img_width;
			ypos = i * img_height;
			put_image(map[i][j], game, xpos, ypos);
			j++;
		}
		i++;
	}
	count = ft_itoa(game->count);
	count = ft_strjoin("moves : ", count);
	mlx_string_put(game->mlx, game->window, 20, 20, 0xFFFFFF, count);
}
