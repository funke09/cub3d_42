#include "cub3d.h"

void ft_window(t_map *map)
{
    map->game.mlx = mlx_init();
    map->game.width = map->res_x;
    map->game.height = map->res_y;
    map->game.window = mlx_new_window(map->game.mlx, map->game.width, map->game.height, "Cub3D");
}

// void ft_map(t_map *map)
// {
//     map->
// }

void init_start(t_map *map)
{
    ft_window(map);
    // ft_map(map);
    // ft_player(map);
    // ft_sprite(map);
    // ft_texture(map);
}

int init_game(t_map *map)
{
    init_start(map);
    mlx_loop(map->game.mlx);
    return (1);
}