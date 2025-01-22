/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:31:47 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/22 11:44:56 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "so_long.h"
#include <mlx.h>
#include <fcntl.h>

void	load_frames(t_game *game)
{
	int	height;
	int	width;

	game->frames[0] = mlx_xpm_file_to_image(game->mlx, \
	"srcs/fire1.xpm", &width, &height);
	game->frames[1] = mlx_xpm_file_to_image(game->mlx, \
	"srcs/fire2.xpm", &width, &height);
	game->frames[2] = mlx_xpm_file_to_image(game->mlx, \
	"srcs/fire4.xpm", &width, &height);
	game->frames[3] = mlx_xpm_file_to_image(game->mlx, \
	"srcs/fire5.xpm", &width, &height);
	game->frames[4] = mlx_xpm_file_to_image(game->mlx, \
	"srcs/fire6.xpm", &width, &height);
}

void	animation(t_game *game, int xpos, int ypos)
{
	int	delay;
	int	total_frames;
	int	i;

	delay = 4000;
	total_frames = 5;
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].x == xpos && game->enemies[i].y == ypos)
		{
			if (game->enemies[i].counter++ >= delay)
			{
				mlx_put_image_to_window(game->mlx, game->window, \
				game->frames[game->enemies[i].frame], xpos, ypos);
				game->enemies[i].frame++;
				if (game->enemies[i].frame >= total_frames)
					game->enemies[i]. frame = 0;
				game->enemies[i].counter = 0;
			}
			break ;
		}
		i++;
	}
}

void	fill_enemies(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'X')
			{
				game->enemies[count].x = j * game->img_width;
				game->enemies[count].y = i * game->img_height;
				game->enemies[count].frame = 0;
				game->enemies[count].counter = 0;
				count++;
			}
			j++;
		}
		i++;
	}
}

void	initialize_enemies(t_game *game)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	count = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'X')
				count++;
			j++;
		}
		i++;
	}
	game->enemy_count = count;
	game->enemies = malloc(sizeof(t_enemy) * count);
	fill_enemies(game);
}

int	put_enemy(t_game *game)
{
	int		i;
	int		j;
	int		xpos;
	int		ypos;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			xpos = j * game->img_width;
			ypos = i * game->img_height;
			if (game->map[i][j] == 'X')
				animation(game, xpos, ypos);
			j++;
		}
		i++;
	}
	return (0);
}
