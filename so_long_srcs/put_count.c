/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:29:17 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/30 15:09:09 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_holder(t_game *game)
{
	int	width;
	int	height;

	game->digits[0] = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/Fonts/0.xpm", &width, &height);
	game->digits[1] = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/Fonts/1.xpm", &width, &height);
	game->digits[2] = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/Fonts/2.xpm", &width, &height);
	game->digits[3] = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/Fonts/3.xpm", &width, &height);
	game->digits[4] = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/Fonts/4.xpm", &width, &height);
	game->digits[5] = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/Fonts/5.xpm", &width, &height);
	game->digits[6] = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/Fonts/6.xpm", &width, &height);
	game->digits[7] = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/Fonts/7.xpm", &width, &height);
	game->digits[8] = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/Fonts/8.xpm", &width, &height);
	game->digits[9] = mlx_xpm_file_to_image(game->mlx, \
	"./sprites/Fonts/9.xpm", &width, &height);
}

void	put_digit(t_game *game, int digit, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, game->digits[digit], x, y);
}

void	put_count(t_game *game, int count)
{
	char	*buffer;
	int		i;
	int		digit;

	buffer = ft_itoa(count);
	i = 0;
	mlx_put_image_to_window(game->mlx, game->window, \
	game->moves, 0, 0);
	while (buffer[i])
	{
		digit = buffer[i] - '0';
		put_digit(game, digit, 90 + (i * 15), 13);
		i++;
	}
	free(buffer);
}
