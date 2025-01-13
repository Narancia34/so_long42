/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mvt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:05:19 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/13 12:55:30 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <mlx.h>

int	is_exit_valid(t_game *game)
{
	int		j;
	int		i;

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
	return (0);
}

void	wasd_mvt(t_npos *npos, t_game *game)
{
	if (game->keypress == ESC_KEY)
		exit(0);
	if (game->keypress== 'w')
		npos->n_ypos--;
	else if (game->keypress == 's')
		npos->n_ypos++;
	else if (game->keypress == 'a')
	{
		game->flag = 1;
		npos->n_xpos--;
	}
	else if (game->keypress == 'd')
	{
		npos->n_xpos++;
		game->flag = 2;
	}
}

int handle_keypress(t_game *game)
{
	t_npos npos;
	
	npos.n_xpos = game->p_xpos;
    npos.n_ypos = game->p_ypos;
	wasd_mvt(&npos, game);
	if (game->map[npos.n_ypos][npos.n_xpos] == '1')
		return (0);
	else if (game->map[npos.n_ypos][npos.n_xpos] == 'X')
		exit(0);
	else if (game->map[npos.n_ypos][npos.n_xpos] == 'E')
	{
		if (is_exit_valid(game) == 0)
			exit(0);
	}
	else if (game->p_xpos != npos.n_xpos || game->p_ypos != npos.n_ypos)
	{
		game->map[game->p_ypos][game->p_xpos] = '0';
		game->map[npos.n_ypos][npos.n_xpos] = 'P';
		render_map(game, game->map, game->img_width, game->img_width);
		game->count++;
		game->p_xpos = npos.n_xpos;
		game->p_ypos = npos.n_ypos;
	}
	game->keypress = 0;
	return (0);
}

int	loop(t_game *game)
{
	put_enemy(game);
	handle_keypress(game);
	return(0);
}

int	get_keycode(int keycode, t_game *game)
{
	game->keypress = keycode;
    return (0);
}