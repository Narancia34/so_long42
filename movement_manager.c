/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:52:49 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/11 17:04:38 by mgamraou         ###   ########.fr       */
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

int	key_press(int keycode, t_game *game)
{
	if (keycode == 'w')
        game->keys->w = 1;
    else if (keycode == 'a')
        game->keys->a = 1;
    else if (keycode == 's')
        game->keys->s = 1;
    else if (keycode == 'd')
        game->keys->d = 1;
	if (keycode == ESC_KEY)
		exit(0);
	//keycode = 0;
	return (0);
}

int	key_release(int keycode , t_game *game)
{
	if (keycode == 'w')
        game->keys->w = 0;
    else if (keycode == 'a')
        game->keys->a = 0;
    else if (keycode == 's')
        game->keys->s = 0;
    else if (keycode == 'd')
        game->keys->d = 0;
	return (0);
}

void update_player_position(t_game *game)
{
    t_npos npos;
	
    npos.n_xpos = game->p_xpos;
    npos.n_ypos = game->p_ypos;
	render_map(game, game->map, game->img_width, game->img_width);
    if (game->keys->w == 1)
        npos.n_ypos--;
    else if (game->keys->s == 1)
        npos.n_ypos++;
    else if (game->keys->a == 1)
        npos.n_xpos--;
    else if (game->keys->d == 1)
        npos.n_xpos++;

    if (game->map[npos.n_ypos][npos.n_xpos] == '1')
		return ;
	else if (game->map[npos.n_ypos][npos.n_xpos] == 'X')
		exit(0);
	else if (game->map[npos.n_ypos][npos.n_xpos] == 'E')
	{
		if (is_exit_valid(game) == 1)
			exit(0);
		// mlx_clear_window(game->mlx, game->window);
	}
	else if (game->p_xpos != npos.n_xpos || game->p_ypos != npos.n_ypos)
	{
		game->map[game->p_ypos][game->p_xpos] = '0';
		game->map[npos.n_ypos][npos.n_xpos] = 'P';
		//mlx_clear_window(game->mlx, game->window);
		render_map(game, game->map, game->img_width, game->img_width);
		game->count++;
		game->p_xpos = npos.n_xpos;
		game->p_ypos = npos.n_ypos;
	}
}


int	game_loop(t_game *game)
{
	//animation(game);
	update_player_position(game);
    return (0);
}
