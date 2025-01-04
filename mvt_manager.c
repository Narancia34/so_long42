/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvt_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:26:00 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/04 17:26:02 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <mlx.h>

void	wasd_move(int keycode, t_game *game, t_npos *npos)
{

	npos->n_xpos = game->p_xpos;
	npos->n_ypos = game->p_ypos;
	if (keycode == ESC_KEY)
		exit(0);
	if (keycode == 'w')
		npos->n_ypos--;
	else if (keycode == 's')
		npos->n_ypos++;
	else if (keycode == 'a')
		npos->n_xpos--;
	else if (keycode == 'd')
		npos->n_xpos++;
}

// int	is_exit_valid(t_game *game)
// {
// 	int		j;
// 	int		i;

// 	while (game->map[i])
// 		{
// 			j = 0;
// 			while (game->map[i][j])
// 			{
// 				if (game->map[i][j] == 'C')
// 					return (1);
// 				j++;
// 			}
// 			i++;
// 		}
// }

int	key_press(int keycode, t_game *game)
{
	int		j;
	int		i;
	t_npos npos;
	
	wasd_move(keycode, game, &npos);
	if (game->map[npos.n_ypos][npos.n_xpos] == '1')
		return (1);
	else if (game->map[npos.n_ypos][npos.n_xpos] == 'X')
		mlx_clear_window(game->mlx, game->window);
	else if (game->map[npos.n_ypos][npos.n_xpos] == 'E')
	{
		i = 0;
		while (game->map[i])
		{
			j = 0;
			while (game->map[i][j])
			{
				if (game->map[i][j] == 'C')
					return (1);
				j++;
			}
			i++;
		}
		mlx_clear_window(game->mlx, game->window);
	}
	else
	{
		game->map[game->p_ypos][game->p_xpos] = '0';
		game->map[npos.n_ypos][npos.n_xpos] = 'P';
		game->count++;
		mlx_clear_window(game->mlx, game->window);
		render_map(game, game->map, game->img_width, game->img_width);
		game->p_xpos = npos.n_xpos;
		game->p_ypos = npos.n_ypos;
	}
}
