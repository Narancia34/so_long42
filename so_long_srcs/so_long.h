/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:08:32 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/31 14:14:50 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define ESC_KEY 65307

# include <mlx.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include "get_next_line.h"
# include <stddef.h>
# include <unistd.h>
# include "../ft_printf/libftprintf.h"

typedef struct s_data
{
	int	rows;
	int	cols;
	int	exit;
	int	player;
	int	collectibles;
}	t_data;

typedef struct s_enemy
{
	int	x;
	int	y;
	int	frame;
	int	counter;
}	t_enemy;

typedef struct s_game
{
	void	*mlx;
	void	*window;
	void	*ground;
	void	*wall;
	void	*right_player;
	void	*left_player;
	void	*body;
	void	*closedexit;
	void	*moves;
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
	int		enemy_count;
	int		ignore_exit;
	t_enemy	*enemies;
}	t_game;

typedef struct s_npos
{
	int		n_ypos;
	int		n_xpos;
}	t_npos;

int		close_window(t_game *game);
int		map_manager(char **map, t_data *data);
int		check_map_components(char **map, t_data *data);
int		is_surrounded_bywalls(char **map, t_data *data);
int		is_rectangular(char **map, t_data *data);
int		get_keycode(int keycode, t_game *game);
int		handle_keypress(t_game *game);
int		loop(t_game *game);
int		put_enemy(t_game *game);
int		is_path_to_exit(char **map, t_game *game);
int		is_path_to_collect(char **map, t_game *game);
int		check_file(char *filename);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	render_map(t_game *game, char **map, int img_width, int img_height);
void	animation(t_game *game, int xpos, int ypos);
void	fill_holder(t_game *game);
void	put_count(t_game *game, int count);
void	load_frames(t_game *game);
void	initialize_enemies(t_game *game);
void	find_player(char **map, t_game *game);
char	**copy_map(t_game *game, char **map);
char	**get_map(char *name, t_game *game);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_itoa(int n);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlen(const char *s);

#endif