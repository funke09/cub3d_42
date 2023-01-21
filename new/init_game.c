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

    i = 0;
    while (map[i])
        i++;
    return (i);
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
    if (x < y)
        return (x);
    else
        return (y);
}
// for player position 
/*

*/
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

int alpha(char c)
{
    if(c == 'S')
        return(90);
    else if(c == 'N')
        return(270);
    else if(c == 'W')
        return(180);
    else if(c == 'E')
        return(0);
}
void get_x_y(t_info *info, t_player *player, char **tmp)
{
    int i;
    int j;

    i = 0;
    j = 0;
    (void)info;
    while (tmp[i])
    {
        // printf("tmp = %s\n", tmp[i]);
        j = 0;
        while (tmp[i][j])
        {
            if (tmp[i][j] == 'N' || tmp[i][j] == 'S' || tmp[i][j] == 'W' || tmp[i][j] == 'E')
            {
                player->p_x = ((float)j + 0.5)* TILE_SIZE;
                player->p_y = ((float)i + 0.5)* TILE_SIZE;
                printf("player->p_x = %f\n", player->p_x);
                printf("player->p_y = %f\n", player->p_y);
                // printf("tmp[i][j] = %c\n", tmp[i][j]);
                player->rot_angle = rotation(tmp[i][j]);
                player->radius = alpha(tmp[i][j]);
                // printf("player->rot_angle = %f\n", player->rot_angle);
                return ;
            }
            j++;
        }
        i++;
    }
}

void ft_player(t_map *map)
{
    get_x_y(&map->info, &map->player_t, map->map);
    map->player_t.walk_direction = 0;
    map->player_t.turn_direction = 0;
    map->player_t.move_speed = 0.35;
    map->player_t.rot_speed = 3 * (M_PI / 180);

}

void ft_map(t_map *map)
{
    map->info.full_map = map->map;
    map->info.rows = ft_count_rows(map->info.full_map);
    map->info.cols = ft_count_cols(map->info.full_map);
    // map->info.tile_size = 20;
    map->info.width_map = map->info.tile_size * map->info.cols;
    map->info.height_map = map->info.tile_size * map->info.rows;
//    map->info.full_map = expande_map(map->map, map->info.cols, map->info.rows, map->info.tile_size);
    // printf("rows = %d\n", map->info.rows);
    // printf("cols = %d\n", map->info.cols);
    // printf("width = %d\n", map->info.width_map);
    // printf("height = %d\n", map->info.height_map);
    // printf("tile_size = %d\n", map->info.tile_size);
    // showarray(map->info.full_map);
    
}

int init_texture(t_map *map, t_image *image, char *path)
{
    image->img = mlx_xpm_file_to_image(map->game.mlx, path, &image->width, &image->height);
    // printf("image->img = %p\n", image->img);
    image->addr =(int *) mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length, &image->endian);
    // printf("image->addr = %p\n", image->addr);
    return (0);
}

int ft_texture(t_map *map)
{
    init_texture(map, &map->image, map->no);
    init_texture(map, &map->image, map->so);
    init_texture(map, &map->image, map->we);
    init_texture(map, &map->image, map->ea);
    return (0);
}

int abs(int n) { return ((n > 0) ? n : (n * (-1))); }
 
// DDA Function for line generation
void DDA(int X0, int Y0, int X1, int Y1)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
 
    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++) {
        mlx_pixel_put(round(X), round(Y),
                 RED); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
        delay(100); // for visualization of line-
                    // generation step by step
    }
}

bool player(t_map *map, float i, float j)
{
    float x;
    float y;
    float x1;
    float y1;

    x1 = map->player_t.p_x / TILE_SIZE;
    y1 = map->player_t.p_y / TILE_SIZE;
    x = i / TILE_SIZE;
    y = j / TILE_SIZE;
    return((x-x1) * (x-x1) + (y-y1) * (y-y1) <= 0.16 * 0.16);
}

void print_square(t_map *map, int x, int y, int color)
{
    int i = x;
    int j = y;


    while (i < x + TILE_SIZE - 1)
    {
        j = y;
        while (j < y + TILE_SIZE - 1)
        {
            if(player(map, i, j))
            {
                // printf("here\n");
                mlx_pixel_put(map->game.mlx, map->game.window, i, j, 0xFF0000);
            }
            else
                mlx_pixel_put(map->game.mlx, map->game.window, i, j, color);
            j++;
        }
        i++;
    }
}

void draw_square(t_map *map, char c, int x, int y)
{
    int i;

    i = 0;
    if (c == '1')
        print_square(map, x * TILE_SIZE, y * TILE_SIZE, 0x00FF00);
    else if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
        print_square(map, x * TILE_SIZE, y * TILE_SIZE, 0x0000FF);
    else if (c == ' ')
       print_square(map, x * TILE_SIZE, y * TILE_SIZE, 0x0FFFF0); 
    // else if (player(map, x, y))
    //     print_square(map, x * TILE_SIZE, y * TILE_SIZE, 0x00FF00);
}

void ft_draw(t_map *map)
{
    int i;
    int j;

    i = 0;
    printf("p_x = %f\n", map->player_t.p_x);
    printf("p_y = %f\n", map->player_t.p_y);
    while(map->map[i])
    {
        j = 0;
        while(map->map[i][j])
        {
            draw_square(map, map->map[i][j], j, i);
            j++;
        }
        i++;
    }
  
}

/*
    fov = 60deg convert to rad
    ft_check (map)
    {
        angle = map->player_t.angle - (FOV_ANGLE / 2);
        while (angle < map->player_t.angle + (FOV_ANGLE / 2))
        {
            p = horz_vertic_check(angle map)
            draw__line(p, pla(x,y))
            angle 

        }
    }

*/

void init_start(t_map *map)
{
    ft_window(map);
    ft_map(map);
    ft_player(map);
    ft_draw(map);
    /*
    ft_check (map)    send rays

    */
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