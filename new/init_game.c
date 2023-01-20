#include "cub3d.h"

void ft_window(t_map *map)
{
    map->game.mlx = mlx_init();
    map->game.width = map->res_x;
    map->game.height = map->res_y;
    map->game.window = mlx_new_window(map->game.mlx, map->game.width, map->game.height, "Cub3D");
}

int ft_count_rows(char **map)
{
    int i;
    int s;
    int j;

    i = -1;
    s = 0;
    j = -1;
    while (map[++i])
    {
        j= -1;
        while (map[i][++j]);
        
        if(j > s)
            s = j;
    }
    // printf("s = %d\n", s);
    return (s);
}

int ft_count_cols(char **map)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
            j++;
        if(j > len)
            len = j;
        i++;
    }
    return (len);
}

int tilsize(t_map *map)
{
   int x;
   int y;

    x = (map->game.width / map->info.cols / 3);
    y = (map->game.height / map->info.rows / 3);
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    if (x < y)
        return (x);
    else
        return (y);
}

float rotation(char c)
{
 
    if (c == 'S')
        return (M_PI_2);
    else if (c == 'N')
        return (3 * M_PI_2);
    else if (c == 'W')
        return (M_PI);
    else if (c == 'E')
        return (0);
    return (0);
}

void get_x_y(t_info *info, t_player *player, char **tmp)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (tmp[i])
    {
        j = 0;
        while (tmp[i][j])
        {
            if (tmp[i][j] == 'N' || tmp[i][j] == 'S' || tmp[i][j] == 'W' || tmp[i][j] == 'E')
            {
                player->p_x = ((float)j + 0.5)* info->tile_size;
                player->p_y = ((float)i + 0.5)* info->tile_size;
                player->rot_angle = rotation(tmp[i][j]);
            }
            j++;
        }
        i++;
    }
}

void ft_player(t_map *map)
{
    get_x_y(&map->info, &map->player_t, map->tmp);
    map->player_t.radius = map->info.tile_size / 6;
    map->player_t.walk_direction = 0;
    map->player_t.turn_direction = 0;
    map->player_t.move_speed = 0.35;
    map->player_t.rot_speed = 7 * (M_PI / 180);

}

void ft_map(t_map *map)
{
    map->info.rows = ft_count_rows(map->map);
    map->info.cols = ft_count_cols(map->map);
    map->info.tile_size = tilsize(map);
    map->info.width_map = map->info.tile_size * map->info.cols;
    map->info.height_map = map->info.tile_size * map->info.rows;
   map->info.full_map = expande_map(map->map, map->info.cols, map->info.rows, map->info.tile_size);
    printf("rows = %d\n", map->info.rows);
    printf("cols = %d\n", map->info.cols);
    printf("width = %d\n", map->info.width_map);
    printf("height = %d\n", map->info.height_map);
    printf("tile_size = %d\n", map->info.tile_size);
    // showarray(map->info.full_map);
    
}



void init_start(t_map *map)
{
    ft_window(map);
    ft_map(map);
    ft_player(map);
    // ft_sprite(map);
    // ft_texture(map);
}
int close_window(t_map *map)
{
    free_loop(map->map);
    mlx_destroy_window(map->game.mlx, map->game.window);
    exit(0);
}

int key_press(int keycode, t_map *map)
{
    if (keycode == ESC)
        close_window(map);
    else if (keycode == W_KEY)
        map->player_t.walk_direction = 'w';
    else if (keycode == A_KEY)
        map->player_t.walk_direction = 'a';
    else if (keycode == S_KEY)
        map->player_t.walk_direction = 's';
    else if (keycode == D_KEY)
        map->player_t.walk_direction = 'd';
    else if (keycode == LEFT)
        map->player_t.turn_direction = -1;
    else if (keycode == RIGHT)
        map->player_t.turn_direction = 1;
    return (0);
}

int key_release(int keycode, t_map *map)
{
    if (keycode == 53)
        close_window(map);
    else if (keycode == W_KEY)
        map->player_t.walk_direction = 0;
    else if (keycode == A_KEY)
        map->player_t.walk_direction = 0;
    else if (keycode == S_KEY)
        map->player_t.walk_direction = 0;
    else if (keycode == D_KEY)
        map->player_t.walk_direction = 0;
    else if (keycode == LEFT)
        map->player_t.turn_direction = 0;
    else if (keycode == RIGHT)
        map->player_t.turn_direction = 0;
    return (0);
}


int close_key(t_map *map)
{
    (void)map;
    exit(0);
    return (0);
}


int init_game(t_map *map)
{
    init_start(map);
    mlx_do_key_autorepeatoff(map->game.mlx);
    mlx_hook(map->game.window, 2, 1L << 0, &key_press, map);
    mlx_hook(map->game.window, 3, 1L << 1, &key_release, map);
    mlx_hook(map->game.window, 17, 1L << 17, &close_key, map);
    mlx_loop(map->game.mlx);
    return (1);
}

void expande_row(char **new_row, char c, int expandsize, int l, int yy)
{
    int i;
    int j;
    int x;
    int y;

    y = yy;
    j = l;
    x = -1;
    i = -1;
    while (++i < expandsize)
    {
        while (++x < expandsize)
        {
            new_row[yy++][j++] = c;
        }
        x = -1;
    }
}


//expand every element from the given matrix with given size
char **expande_map(char **map,int width, int height, int expandsize)
{
    int i;
    int j;
    int k;
    int l;
    char **new_map;

    new_map = malloc(sizeof(char *) * (height * expandsize));
    if(!new_map)
        return (NULL);
    i = -1;
    j = -1;
    k = 0;
    l = 0;
     while (++i < height)
     {
        new_map[i] = malloc(sizeof(char) * (width * expandsize));
        if(!new_map[i])
            return (NULL);// exit
          while (++j < width)
          {
               expande_row(&new_map[k], map[i][j], expandsize, l, k);
                l = l + expandsize;
                k = k + expandsize;
            }
          j = -1;
          
     }
     return (new_map);
        //showarray(new_map);

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