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

void expande_row(char **new_row, char c, int expandsize, int l)
{
    int i;
    int j;

    j = l;
    i = -1;
    while (++i < expandsize)
    {
        while (++j < expandsize)
        {
            new_row[i][j] = c;
        }
        j = l;
    }
}


//expand every element from the given matrix with given size
void expande_map(char **map,int width, int height, int expandsize)
{
    int i;
    int j;
    int k;
    int l;
    char **new_map;

    new_map = malloc(sizeof(char *) * (height * expandsize));
    if(!new_map)
        return ;
    i = -1;
    j = -1;
    k = -1;
    l = -1;
     while (++i < height)
     {
        new_map[i] = malloc(sizeof(char) * (width * expandsize));
        if(!new_map[i])
            return ;
          while (++j < width)
          {
               expande_row(&new_map[k], map[i][j], expandsize, l);
                l = l + expandsize;
          }
          j = -1;
          k = k + expandsize;
     }
        showarray(new_map);

}

void showarray(char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (map[i])
    {
        while (map[i][j])
        {
            printf("%c", map[i][j]);
            j++;
        }
        printf("\n");
        j = 0;
        i++;
    }
}