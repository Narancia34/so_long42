/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:08:32 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/20 10:17:20 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define ESC_KEY 65307

# include <mlx.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>

typedef struct s_data
{
	int	rows;
	int	cols;
	int	exit;
	int	player;
	int	collectibles;
}	t_data;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
}	t_keys;

typedef struct s_frames
{
	void	*frame1;
	void	*frame2;
	void	*frame3;
	void	*frame4;
	void	*frame5;
	void	*frame6;
}	t_frames;

typedef struct s_game
{
	void	*mlx;
	void	*ground;
	void	*wall;
	void	*player;
	void	*right_player;
	void	*left_player;
	void	*vent;
	void	*window;
	void	*exit;
	void	*enemy;
	void	*digits[10];
	void	*frames[5];
	char	**map;
	int		p_xpos;
	int		p_ypos;
	int		img_width;
	int		img_height;
	int		count;
	int		keypress;
	int		flag;
	int		rows;
	int		cols;
	t_keys	*keys;
}	t_game;

typedef struct s_npos
{
	int		n_ypos;
	int		n_xpos;
}	t_npos;

int		map_manager(char **map, t_data *data);
int		check_map_components(char **map, t_data *data);
int		is_surrounded_bywalls(char **map, t_data *data);
int		is_rectangular(char **map, t_data *data);
int		find_path(char **map, int x_pos, int y_pos, char target);
void	render_map(t_game *game, char **map, int img_width, int img_height);
void	find_player(char **map, t_game *game);
int		animation(t_game *game, int xpos, int ypos);
int		get_keycode(int keycode, t_game *game);
int		handle_keypress(t_game *game);
int		loop(t_game *game);
int		put_enemy(t_game *game);
void	fill_holder(t_game *game);
void	put_count(t_game *game, int count);
void	load_frames(t_game *game);

#endif