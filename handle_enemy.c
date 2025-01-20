/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:31:47 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/20 10:18:15 by mgamraou         ###   ########.fr       */
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

	game->frames[0] = mlx_xpm_file_to_image(game->mlx, "srcs/fire1.xpm", &width, &height);
	game->frames[1] = mlx_xpm_file_to_image(game->mlx, "srcs/fire2.xpm", &width, &height);
	game->frames[2] = mlx_xpm_file_to_image(game->mlx, "srcs/fire4.xpm", &width, &height);
	game->frames[3] = mlx_xpm_file_to_image(game->mlx, "srcs/fire5.xpm", &width, &height);
	game->frames[4] = mlx_xpm_file_to_image(game->mlx, "srcs/fire6.xpm", &width, &height);
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

// int	animation(t_game *game, int xpos, int ypos)
// {
// 	static int	frame;
// 	static int	counter;
// 	int			delay;

// 	delay = 40000;
// 	if (counter++ >= delay)
// 	{
// 		if (frame == 0)
// 		{
// 			mlx_put_image_to_window(game->mlx, game->window, \
// 			game->vent, xpos, ypos);
// 			frame = 1;
// 		}
// 		else
// 		{
// 			mlx_put_image_to_window(game->mlx, game->window, \
// 			game->exit, xpos, ypos);
// 			frame = 0;
// 		}
// 		counter = 0;
// 	}
// 	return (0);
// }
int	animation(t_game *game, int xpos, int ypos)
{
	static int	frame;
	static int	counter;
	int			delay;
	int			total_frames;

	delay = 20000;
	total_frames = 5;

	if (counter++ >= delay)
	{
		mlx_put_image_to_window(game->mlx, game->window, game->frames[frame], xpos, ypos);
		frame++;
		if (frame >= total_frames)
			frame = 0;
		counter = 0;
	}

	return (0);
}
