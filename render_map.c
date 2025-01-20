/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:26:21 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/19 17:24:55 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "so_long.h"
#include <mlx.h>

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
	else if (c == 'P')
	{
		if (game->flag == 1)
			mlx_put_image_to_window(game->mlx, \
			game->window, game->left_player, xpos, ypos);
		else if (game->flag == 2)
			mlx_put_image_to_window(game->mlx, \
			game->window, game->right_player, xpos, ypos);
		else
			mlx_put_image_to_window(game->mlx, \
			game->window, game->player, xpos, ypos);
	}
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
	put_count(game, game->count);
}
