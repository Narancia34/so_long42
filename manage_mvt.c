/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mvt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:05:19 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/11 16:54:42 by mgamraou         ###   ########.fr       */
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

void	move_a(t_game *game, t_npos *npos)
{
	char *player_path = "/home/mgamraou/Downloads/player_left.xpm";
	
	npos->n_xpos--;
	game->player = mlx_xpm_file_to_image(game->mlx, player_path, &game->img_width, &game->img_height);
}

void	move_d(t_game *game, t_npos *npos)
{
	char *player_path = "/home/mgamraou/Downloads/player_1_.xpm";
	
	npos->n_xpos++;
	game->player = mlx_xpm_file_to_image(game->mlx, player_path, &game->img_width, &game->img_height);
}

int handle_keypress(t_game *game)
{
	t_npos npos;

	npos.n_xpos = game->p_xpos;
    npos.n_ypos = game->p_ypos;
	if (game->keypress == ESC_KEY)
		exit(0);
	if (game->keypress== 'w')
		npos.n_ypos--;
	else if (game->keypress == 's')
		npos.n_ypos++;
	else if (game->keypress == 'a')
		move_a(game, &npos);
	else if (game->keypress == 'd')
		move_d(game, &npos);

	if (game->map[npos.n_ypos][npos.n_xpos] == '1')
		return (0);
	else if (game->map[npos.n_ypos][npos.n_xpos] == 'X')
		exit(0);
	else if (game->map[npos.n_ypos][npos.n_xpos] == 'E')
	{
		if (is_exit_valid(game) == 0)
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
	game->keypress = 0;
	return (0);
}

// int move_loop(t_game *game)
// {
// 	if (game->keypress == 'w')
//          handle_keypress('w', game);
//     else if (game->keypress == 's')
//         handle_keypress('s', game);
//     else if (game->keypress == 'a')
//         handle_keypress('a', game);
//     else if (game->keypress == 'd')
//         handle_keypress('d', game);

// 	game->keypress = 0;
// }

int	get_keycode(int keycode, t_game *game)
{
	game->keypress = keycode;
    return (0);
}