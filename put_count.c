/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:29:17 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/22 11:46:20 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_holder(t_game *game)
{
	int	width;
	int	height;

	game->digits[0] = mlx_xpm_file_to_image(game->mlx, \
	"/home/mgamraou/Downloads/Fonts/0.xpm", &width, &height);
	game->digits[1] = mlx_xpm_file_to_image(game->mlx, \
	"/home/mgamraou/Downloads/Fonts/1.xpm", &width, &height);
	game->digits[2] = mlx_xpm_file_to_image(game->mlx, \
	"/home/mgamraou/Downloads/Fonts/2.xpm", &width, &height);
	game->digits[3] = mlx_xpm_file_to_image(game->mlx, \
	"/home/mgamraou/Downloads/Fonts/3.xpm", &width, &height);
	game->digits[4] = mlx_xpm_file_to_image(game->mlx, \
	"/home/mgamraou/Downloads/Fonts/4.xpm", &width, &height);
	game->digits[5] = mlx_xpm_file_to_image(game->mlx, \
	"/home/mgamraou/Downloads/Fonts/5.xpm", &width, &height);
	game->digits[6] = mlx_xpm_file_to_image(game->mlx, \
	"/home/mgamraou/Downloads/Fonts/6.xpm", &width, &height);
	game->digits[7] = mlx_xpm_file_to_image(game->mlx, \
	"/home/mgamraou/Downloads/Fonts/7.xpm", &width, &height);
	game->digits[8] = mlx_xpm_file_to_image(game->mlx, \
	"/home/mgamraou/Downloads/Fonts/8.xpm", &width, &height);
	game->digits[9] = mlx_xpm_file_to_image(game->mlx, \
	"/home/mgamraou/Downloads/Fonts/9.xpm", &width, &height);
}

void	put_digit(t_game *game, int digit, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, game->digits[digit], x, y);
}

void	put_count(t_game *game, int count)
{
	char	*buffer;
	int		i;
	int		x;
	int		y;
	int		digit;

	buffer = ft_itoa(count);
	i = 0;
	x = (game->cols / 2) * game->img_width;
	y = (game->rows + 1) * game->img_height;
	mlx_put_image_to_window(game->mlx, game->window, \
	game->moves, x - 150, y - 30);
	while (buffer[i])
	{
		digit = buffer[i] - '0';
		put_digit(game, digit, x + (i * 15), y);
		i++;
	}
	free(buffer);
}
