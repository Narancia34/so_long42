# include "get_next_line.h"
# include "libft.h"
# include "so_long.h"
# include <mlx.h>
# include <fcntl.h>

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

int	animation(t_game *game, int xpos, int ypos)
{
	static int frame;
	static int counter;

	int delay = 40000;

	if (counter++ >= delay)
	{
		if (frame == 0)
		{
			mlx_put_image_to_window(game->mlx, game->window, game->vent, xpos, ypos);
			frame = 1;
		}
		else
		{
			mlx_put_image_to_window(game->mlx, game->window, game->exit, xpos, ypos);
			frame = 0;
		}
		counter = 0;
	}
	return (0);
}
