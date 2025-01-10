/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvt_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:26:00 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/09 17:14:45 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <mlx.h>

void	move_w(t_game *game, t_npos *npos)
{
	char *player_path = "/home/mgamraou/Downloads/player_1_.xpm";
	
	npos->n_ypos--;
	game->player = mlx_xpm_file_to_image(game->mlx, player_path, &game->img_width, &game->img_height);
}

void	move_s(t_game *game, t_npos *npos)
{
	char *player_path = "/home/mgamraou/Downloads/player_1_.xpm";
	
	npos->n_ypos++;
	game->player = mlx_xpm_file_to_image(game->mlx, player_path, &game->img_width, &game->img_height);
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

void	wasd_move(int keycode, t_game *game, t_npos *npos)
{
	npos->n_xpos = game->p_xpos;
	npos->n_ypos = game->p_ypos;
	if (keycode == ESC_KEY)
		exit(0);
	if (keycode == 'w')
		move_w(game, npos);
	else if (keycode == 's')
		move_s(game, npos);
	else if (keycode == 'a')
		move_a(game, npos);
	else if (keycode == 'd')
		move_d(game, npos);
}

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
	int		j;
	int		i;
	t_npos	npos;

	wasd_move(keycode, game, &npos);
	if (game->map[npos.n_ypos][npos.n_xpos] == '1')
		return (1);
	else if (game->map[npos.n_ypos][npos.n_xpos] == 'X')
		mlx_clear_window(game->mlx, game->window);
	else if (game->map[npos.n_ypos][npos.n_xpos] == 'E')
	{
		if (is_exit_valid(game) == 1)
			return (1);
		exit(0);
	}
	else
	{
		game->map[game->p_ypos][game->p_xpos] = '0';
		game->map[npos.n_ypos][npos.n_xpos] = 'P';
		mlx_clear_window(game->mlx, game->window);
		render_map(game, game->map, game->img_width, game->img_width);
		game->count++;
		game->p_xpos = npos.n_xpos;
		game->p_ypos = npos.n_ypos;
	}
}
