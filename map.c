#include <mlx.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#define ESC_KEY 65307

typedef struct s_game {
    void *mlx;
    void *ground;
    void *wall;
    void *player;
    void *window;
    char **map;
    int p_xpos;
    int p_ypos;
    int		img_width;
	int		img_height;
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
                return (printf("Error: not surrounded by walls"), 0);
            if (map[i][j] == 'P')
                player_spos++;
            else if (map[i][j] == 'E')
                exit++;
            else if (map[i][j] == 'C')
                collectible++;
            else if (map[i][j] != '0' && map[i][j] != '1')
                return (printf("Error: extra obj"), 0);
            j++;
        }
        j = 0;
        i++;
    }
    if (player_spos != 1 || exit != 1 || collectible < 1)
        return (printf("Error: extra player || exit || 0 collectible"), 0);
    return (1);

}

int find_path(char **map, int x_pos, int y_pos, char target, char check)
{

    if (map[x_pos][y_pos] == check || map[x_pos][y_pos] == '1')
        return 0;
    if (map[x_pos][y_pos] == 'E')
        return 1;
    map[x_pos][y_pos] = check;

    if (find_path(map, x_pos + 1, y_pos, target, check)) // south
        return 1; 
    if (find_path(map, x_pos - 1, y_pos, target, check)) // north
        return 1; 
    if (find_path(map, x_pos, y_pos + 1, target, check)) // east
        return 1; 
    if (find_path(map, x_pos, y_pos - 1, target, check)) // west
        return 1;

    return 0;
}

int close_window(void *param)
{
    (void)param;
    exit(0);
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
                // mlx_put_image_to_window(game->mlx, game->window, game->ground, xpos, ypos);
                mlx_put_image_to_window(game->mlx, game->window, game->player, xpos, ypos);
            }
        }
    }
    mlx_string_put(game->mlx, game->window, 20, 20, 0xFFFF00, "hello world!");
}

void find_player(char **map, t_game *game)
{
    int i = 0;
    int j;
    while (map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if (map[i][j] == 'P')
            {
                game->p_xpos = j;
                game->p_ypos = i;
            }
            j++;
        }
        i++;
    }
}

int key_press(int keycode, t_game *game)
{
    char *gamover_path = "/home/mgamraou/Downloads/gettyimages-1325433246-640x640.xpm";
    int a,b;
    void *gameover = mlx_xpm_file_to_image(game->mlx, gamover_path, &a, &b);
    int n_xpos = game->p_xpos;
    int n_ypos = game->p_ypos;
    if (keycode == ESC_KEY)
        exit(0);
    if (keycode == 'w')
        n_ypos--;
    else if (keycode == 's')
        n_ypos++;
    else if (keycode == 'a')
        n_xpos--;
    else if (keycode == 'd')
        n_xpos++;
    if (game->map[n_ypos][n_xpos] == '1')
        return 1;
    else if (game->map[n_ypos][n_xpos] == 'E')
    {
        int i = 0;
        int j;
        while (game->map[i])
        {
            j = 0;
            while(game->map[i][j])
            {
                if (game->map[i][j] == 'C')
                {
                    return 1;
                }
                j++;
            }
            i++;
        }
        mlx_clear_window(game->mlx, game->window);
        mlx_put_image_to_window(game->mlx, game->window, gameover, 0, 0);
    }
    else 
    {
        game->map[game->p_ypos][game->p_xpos] = '0';
        game->map[n_ypos][n_xpos] = 'P';
        mlx_clear_window(game->mlx, game->window);
        render_map(game, game->map, game->img_width, game->img_width);
        game->p_xpos = n_xpos;
        game->p_ypos = n_ypos;
    }

}


int main(const char *argc)
{
    char *map[] = {
        "1111111111111111111111111111111111",
        "1P100001C0000000010C00100001000C01",
        "1C00010111111001010000111011000011",
        "1011110100001001C1C00C001110001001",
        "100001010000110001110110001C011001",
        "1C111100010000C0010C0100001111C001",
        "101000010111111111000100100C100011",
        "10111C0100000000010001011000101001",
        "1010CC01111111110110110100111010C1",
        "1C10100000000001001010010010001111",
        "1011111100010001001010110010000001",
        "1000C00111110101000010C11111110101",
        "1C0010010C01C101011111111C0001C001",
        "11111001100101011100C0E00001000001",
        "100C0000C0000100000110001001001CC1",
        "1111111111111111111111111111111111",
        NULL
    };

    t_game game;
    char	*ground_path = "/home/mgamraou/Downloads/floor_1_.xpm";
    char	*wall_path = "/home/mgamraou/Downloads/Window-2.xpm";
    char    *palyer_path = "/home/mgamraou/Downloads/player_1_.xpm";
    
    game.mlx = mlx_init();
    game.ground = mlx_xpm_file_to_image(game.mlx, ground_path, &game.img_width, &game.img_height);
    game.player = mlx_xpm_file_to_image(game.mlx, palyer_path, &game.img_width, &game.img_height);
    game.wall = mlx_xpm_file_to_image(game.mlx, wall_path, &game.img_width, &game.img_height);
    game.window = mlx_new_window(game.mlx, 2000, 2000, "2D Game Map");

    if (check_map(map) == 0)
            exit(0);
    int rows = 0;
    int cols = strlen(map[0]);
    while (map[rows] != NULL)
        rows++;
    char **map_copy = malloc(rows * sizeof(char *));
    game.map = malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++)
    {
        map_copy[i] = strdup(map[i]);
        game.map[i] = strdup(map[i]);
    }
    if (find_path(map_copy, 4, 2, '0', '2') == 0)
        exit(0);
    for (int i = 0; i < rows; i++)
    {
        free(map_copy[i]);
    }
    free(map_copy);

    //render_map(&game, game.map, game.img_width, game.img_height);
    find_player(map, &game);

    mlx_key_hook(game.window, key_press, &game);
    mlx_hook(game.window, 17, 0, close_window, NULL);
    

    mlx_loop(game.mlx);

    return (0);
}
