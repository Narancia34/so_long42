#include "/home/mgamraou/Downloads/minilibx-linux/mlx.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define ESC_KEY 65307

typedef struct s_game {
    void *mlx;
    void *ground;
    void *wall;
    void *test;
    void *window;
    int tile_size;
} t_game;


int check_map(char **map)
{
    int rows = 0;
    int cols = 0;
    int player_spos = 0;
    int exit = 0;
    int collectible = 0;
    int i = 0;
    int j = 0;
    
    while (map[i])
    {
        if (i == 0)
            cols = strlen(map[i]);
        else if ((int)strlen(map[i]) != cols)
            return (printf("Error: Map is not rectangular\n"), 0);
        rows++;
        i++;
    }
    i = 0;
    while (i < rows)
    {
        while (j < cols)
        {
            if ((i == 0 || i == rows - 1 || j == 0 || j == cols - 1) && map[i][j] != '1')
                return (printf("not surrounded by walls"), 0);
            if (map[i][j] == 'P')
                player_spos++;
            else if (map[i][j] == 'E')
                exit++;
            else if (map[i][j] == 'C')
                collectible++;
            else if (map[i][j] != '0' && map[i][j] != '1')
                return (printf("extra obj"), 0);
            j++;
        }
        j = 0;
        i++;
    }
    if (player_spos != 1 || exit != 1 || collectible < 1)
        return (printf("extra player or extra exit or 0collectible"), 0);
    return (1);

}

int close_window(void *param)
{
    (void)param;
    exit(0);
}

int key_press(int keycode, void *param)
{
	if (keycode == ESC_KEY)
		close_window(param);
	return (0);
}

void draw_tile(t_game *game, int x, int y, int color, int img_width, int img_height)
{
    int i, j;
    //int tile_size = game->tile_size;

    for (i = 0; i < img_height; i++) {
        for (j = 0; j < img_width; j++) {
            mlx_pixel_put(game->mlx, game->window, x * img_width + j, y * img_height + i, color);
        }
    }
}

void render_map(t_game *game, char **map, int img_width, int img_height)
{
    int i, j;

    for (i = 0; map[i]; i++) {
        for (j = 0; map[i][j]; j++) {
            int xpos = j * img_width;
            int ypos = i * img_height;
            if (map[i][j] == '1')
                mlx_put_image_to_window(game->mlx, game->window, game->wall, xpos, ypos);
            else if (map[i][j] == '0')
                mlx_put_image_to_window(game->mlx, game->window, game->ground, xpos, ypos);
            else if (map[i][j] == 'C')
                draw_tile(game, j, i, 0xFFFF00, img_width, img_height); // Yellow for collectibles
            else if (map[i][j] == 'E')
                draw_tile(game, j, i, 0xFF0000, img_width, img_height); // Red for exit
            else if (map[i][j] == 'P')
            {
                mlx_put_image_to_window(game->mlx, game->window, game->ground, xpos, ypos);
                mlx_put_image_to_window(game->mlx, game->window, game->test, xpos, ypos);
            }
        }
    }
}

int main()
{
    char *map[] = {
        "1111111111111",
        "10010000000C1",
        "1000011111001",
        "1P0011E000001",
        "1111111111111",
        "1111111111111",
        NULL
    };
    t_game game;
    char	*ground_path = "/home/mgamraou/Downloads/grass.xpm";
    char	*wall_path = "/home/mgamraou/Downloads/complexgrass.xpm";
    char    *test = "/home/mgamraou/Downloads/image.xpm";
	int		img_width;
	int		img_height;
    //game.tile_size = 50;
    game.mlx = mlx_init();
    game.ground = mlx_xpm_file_to_image(game.mlx, ground_path, &img_width, &img_height);
    game.test = mlx_xpm_file_to_image(game.mlx, test, &img_width, &img_height);
    game.wall = mlx_xpm_file_to_image(game.mlx, wall_path, &img_width, &img_height);
    game.window = mlx_new_window(game.mlx, 2000, 2000, "2D Game Map");

    if (check_map(map) == 0)
            exit(0);
    render_map(&game, map, img_width, img_height);

    mlx_key_hook(game.window, key_press, NULL);
    mlx_hook(game.window, 17, 0, close_window, NULL);

    mlx_loop(game.mlx);

    return (0);
}
