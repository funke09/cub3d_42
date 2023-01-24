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
    return (0);
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

void rays_init(t_map *map)
{
    map->rays.fov = 60 * (M_PI / 180);
    map->rays.strip_width = 1;
    map->rays.ray_num = map->game.width / map->rays.strip_width;
    map->rays.fov_m = 2 * M_PI - (map->rays.fov / 2);
    map->rays.fov_x = (map->rays.fov / 2);
    map->rays.d_p_p = (map->game.width / 2) / tan(map->rays.fov / 2);
}

int abs(int n) 
{
    if(n < 0)
        return (-n);
    return (n);
}
 
// DDA Function for line generation
// void DDA(int X0, int Y0, int X1, int Y1)
// {
//     // calculate dx & dy
//     int dx = X1 - X0;
//     int dy = Y1 - Y0;
 
//     // calculate steps required for generating pixels
//     int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
//     // calculate increment in x & y for each steps
//     float Xinc = dx / (float)steps;
//     float Yinc = dy / (float)steps;
 
//     // Put pixel for each step
//     float X = X0;
//     float Y = Y0;
//     for (int i = 0; i <= steps; i++) {
//         mlx_pixel_put(round(X), round(Y),
//                  RED); // put pixel at (X,Y)
//         X += Xinc; // increment in x at each step
//         Y += Yinc; // increment in y at each step
//         delay(100); // for visualization of line-
//                     // generation step by step
//     }
// }



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
/* to prevent the angle in radians to turn negative or above 2PI */
float to_rad(float num)
{
    if(num >= (2 * M_PI))
        return (num - (2 * M_PI));
    else if(num < 0)
        return (num + (2 * M_PI));
    else
        return (num);
}

int is_wall(t_map *map, float x, float y)
{
    int i;
    int j;

    if((int)x < 0 || (int)x > map->game.width || (int)y < 0 || (int)y > map->game.height)
        return (1);
    i = (int)y / TILE_SIZE;
    j = (int)x / TILE_SIZE;
    if(i >= (int)ft_strlen(map->map[j]))
        return (1);
    if (map->map[(int)i][(int)j] == '1')
            return (1);
    return (0);
}

void get_new_pos(t_map *map)
{
    float step;
    float new_x;
    float new_y;
    float angle;

    if(map->player_t.walk_direction == 0)
        return;
    angle = map->player_t.rot_angle;
    if(map->player_t.walk_direction == 'w')
        angle = to_rad(angle);
    else if(map->player_t.walk_direction == 's')
        angle = to_rad(angle + M_PI);
    else if(map->player_t.walk_direction == 'a')
        angle = to_rad(angle - M_PI_2);
    else if(map->player_t.walk_direction == 'd')
        angle = to_rad(angle + M_PI_2);
    step = map->player_t.move_speed * TILE_SIZE;
    new_x = map->player_t.p_x + (cos(angle) * step);
    new_y = map->player_t.p_y + (sin(angle) * step);
    if(!is_wall(map, new_x, new_y))
    {
        map->player_t.p_x = new_x;
        map->player_t.p_y = new_y;
    }
    
}

void movement_init(t_map *map)
{
    if(map->player_t.turn_direction == 0)
        return;
    map->player_t.rot_angle = to_rad(map->player_t.rot_angle +
     (map->player_t.turn_direction * map->player_t.move_speed));
    get_new_pos(map);
}


int update_rayes(float angle, t_rays *ray)
{
    ray->wall_hit_x = 0;
    ray->wall_hit_y = 0;
    ray->v_hit = 0;
    ray->hor_wall = 0;
    ray->ver_wall = 0;
    ray->hor_x = 0;
    ray->hor_y = 0;
    ray->ver_x = 0;
    ray->ver_y = 0;
    if(angle > 0 && angle < M_PI)
        ray->is_ray_facing_down = 1;
    else
        ray->is_ray_facing_down = 0;
    if(angle > M_PI_2 || angle < (3 * M_PI_2))
        ray->is_ray_facing_left = 1;
    else
        ray->is_ray_facing_left = 0;
    return (0);

}

int H_interstep(t_rays *ray, t_map *map, float *x, float *y)
{
   float y_intercept;
    float x_intercept;

    y_intercept = floor(map->player_t.p_y / TILE_SIZE) * TILE_SIZE;
    if(ray->is_ray_facing_down)
        y_intercept += TILE_SIZE;
    x_intercept = map->player_t.p_x + (y_intercept - map->player_t.p_y) / tan(ray->ray_angle);
    ray->h_step_y = TILE_SIZE;
    if(!ray->is_ray_facing_down)
        ray->h_step_y *= -1;
    ray->h_step_x = TILE_SIZE / tan(ray->ray_angle);
    if(ray->is_ray_facing_left && ray->h_step_x > 0)
        ray->h_step_x *= -1;
    if(!ray->is_ray_facing_left && ray->h_step_x < 0)
        ray->h_step_x *= -1;
    *x = x_intercept;
    *y = y_intercept;
    return (0);
}

int hor_up(t_rays *ray, t_map *map, float *x, float *y)
{
    if(!ray->is_ray_facing_down)
    {
        while(*y >= 0 && *y <= map->game.height && *x >= 0 && *x <= map->game.width)
        {
            if(is_wall(map, *x, *y - 1))
            {
                ray->hor_wall = 1;
                ray->hor_x = *x;
                ray->hor_y = *y;
                break;
            }
            else
            {
                *x += ray->h_step_x;
                *y += ray->h_step_y;
            }
        }
    }
    return (0);
}

int hor_down(t_rays *ray, t_map *map, float *x, float *y)
{
    if(ray->is_ray_facing_down)
    {
        while(*y >= 0 && *y <= map->game.height && *x >= 0 && *x <= map->game.width)
        {
            if(is_wall(map, *x, *y + 1))
            {
                ray->hor_wall = 1;
                ray->hor_x = *x;
                ray->hor_y = *y;
                return (0);
            }
            else
            {
                *x += ray->h_step_x;
                *y += ray->h_step_y;
            }
        }
    }
    return (0);
}

int V_interstep(t_rays *ray, t_map *map, float *x, float *y)
{
    float y_intercept;
    float x_intercept;

    x_intercept = floor(map->player_t.p_x / TILE_SIZE) * TILE_SIZE;
    if(!ray->is_ray_facing_left)
        x_intercept += TILE_SIZE;
    y_intercept = map->player_t.p_y + (x_intercept - map->player_t.p_x) * tan(ray->ray_angle);
    ray->v_step_x = TILE_SIZE;
    if(!ray->is_ray_facing_left)
        ray->v_step_x *= -1;
    ray->v_step_y = TILE_SIZE * tan(ray->ray_angle);
    if(ray->is_ray_facing_down && ray->v_step_y > 0)
        ray->v_step_y *= -1;
    if(!ray->is_ray_facing_down && ray->v_step_y < 0)
        ray->v_step_y *= -1;
    *x = x_intercept;
    *y = y_intercept;
    return (0);
}

int ver_right(t_rays *ray, t_map *map, float *x, float *y)
{
    if(!ray->is_ray_facing_left)
    {
        while(*y >= 0 && *y <= map->game.height && *x >= 0 && *x <= map->game.width)
        {
            if(is_wall(map, *x + 1, *y))
            {
                ray->ver_wall = 1;
                ray->ver_x = *x;
                ray->ver_y = *y;
                return(0);
            }
            else
            {
                *x += ray->v_step_x;
                *y += ray->v_step_y;
            }
        }
    }
    return (0);
}

int ver_left(t_rays *ray, t_map *map, float *x, float *y)
{
    if(ray->is_ray_facing_left)
    {
        while(*y >= 0 && *y <= map->game.height && *x >= 0 && *x <= map->game.width)
        {
            if(is_wall(map, *x - 1, *y))
            {
                ray->ver_wall = 1;
                ray->ver_x = *x;
                ray->ver_y = *y;
                break;
            }
            else
            {
                *x += ray->v_step_x;
                *y += ray->v_step_y;
            }
        }
    }
    return (0);
}

int horz_check(t_map *map, t_rays *ray)
{
    float x;
    float y;

    H_interstep(ray, map, &x, &y);
    hor_up(ray, map, &x, &y);
    hor_down(ray, map, &x, &y);
    return (0);
}


int vert_check(t_map *map, t_rays *ray)
{
    float x;
    float y;

    V_interstep(ray, map, &x, &y);
    ver_left(ray, map, &x, &y);
    ver_right(ray, map, &x, &y);
    return (0);
}

float distance(float x1, float y1, float x2, float y2)
{
    return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void horz_vertic_check(t_map *map, t_rays *ray, float *h_d, float *v_d)
{
    if(ray->hor_wall)
        *h_d = distance(map->player_t.p_x, map->player_t.p_y, ray->hor_x, ray->hor_y);
    else
        *h_d = INT_MAX;
    if(ray->ver_wall)
        *v_d = distance(map->player_t.p_x, map->player_t.p_y, ray->ver_x, ray->ver_y);
    else
        *v_d = INT_MAX;
    if(*h_d < *v_d)
    {
        ray->wall_hit_x = ray->hor_x;
        ray->wall_hit_y = ray->hor_y;
        ray->distance = *h_d;
        ray->v_hit = 0;
    }
    else
    {
        ray->wall_hit_x = ray->ver_x;
        ray->wall_hit_y = ray->ver_y;
        ray->distance = *v_d;
        ray->v_hit = 1;
    }
}

int DDA(t_map *map, t_rays *ray)
{
    float hor_D;
    float ver_D;

    horz_check(map, ray);
    vert_check(map, ray);
    horz_vertic_check(map, ray, &hor_D, &ver_D);
    return (0);
}

int draw_rays(t_map *map)
{
    t_rays *ray;
    int i;

    i = 0;
    ray = &map->rays;
    ray->ray_angle = to_rad(map->player_t.rot_angle - (map->rays.fov / 2));
    while (i < map->rays.ray_num)
    {
        update_rayes(ray->ray_angle, ray);
        DDA(map, ray);
        // draw_line(&ray, map, i, ray.ray_angle);
        // ray.ray_angle += to_rad(ray.ray_angle + (map->rays.fov / map->rays.ray_num));
        i++;
    }
    return (0);
}

int ft_draw_map(t_map *map, int w, int h)
{
    int x;
    int y;

    x = w / TILE_SIZE;
    y = h / TILE_SIZE;
    if(x >= (int)ft_strlen(map->map[y]))
        return (0);
    else if(map->map[y][x] == '1')
        map->image3d.addr[h * map->game.width + w] = 0xa0ea68;
    else if(map->map[y][x] == '2' || map->map[y][x] == '0' || map->map[y][x] == 'N' 
    || map->map[y][x] == 'S' || map->map[y][x] == 'E' || map->map[y][x] == 'W')
        map->image3d.addr[h * map->game.width + w] = 0xd1c3a3;
    else
        return (0);
    return (1);

}

int circle(t_map *map, int w, int h)
{
    if(sqrt(pow(map->player_t.p_x - w, 2) + pow(map->player_t.p_y - h, 2)) <= map->player_t.radius)
        map->image3d.addr[h * map->game.width + w] = 0xc923bb;
    return (0);
}

int ft_initline(t_map *map)
{
    map->line.x_s = map->player_t.p_x;
    map->line.y_s = map->player_t.p_y;
    map->line.x_e = map->player_t.p_x + (cos(map->player_t.rot_angle) * TILE_SIZE);
    map->line.y_e = map->player_t.p_y + (sin(map->player_t.rot_angle) * TILE_SIZE);
    map->line.dx = map->line.x_e - map->line.x_s;
    map->line.dy = map->line.y_e - map->line.y_s;
    map->line.pixl = sqrt(pow(map->line.dx, 2) + pow(map->line.dy, 2));
    map->line.dx = map->line.dx / map->line.pixl;
    map->line.dy = map->line.dy / map->line.pixl;
    map->line.color = 0x754371;
    return (0);
}

int the_line(t_line line, t_map *map)
{
    float x;
    float y;
    int i;

    x = line.x_s;
    y = line.y_s;
    i = 0;
    while (i < line.pixl)
    {
        map->image3d.addr[(int)y * map->game.width + (int)x] = line.color;
        x += line.dx;
        y += line.dy;
        i++;
    }
    return (0);
}

void draw_the_map(int(*f)(t_map *, int , int), t_map *map)
{
    int w;
    int h;

    h = 0;
    while (h < map->game.height)
    {
        w = 0;
        while (w < map->game.width)
        {
            f(map, w, h);
            w++;
        }
        h++;
    }
}

int draw_map(t_map *map)
{
    draw_the_map(&ft_draw_map, map);
    draw_circle(&circle, map);
    ft_initline(map);
    the_line(map->line, map);

}

void init_start(t_map *map)
{
    ft_window(map);
    ft_map(map);
    ft_player(map);
    rays_init(map);

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


int ft_check(t_map *map)
{
    movement_init(map);
    draw_rays(map);
    ft_draw(map);
    draw_map(map);
    mlx_put_image_to_window(map->game.mlx, map->game.window, map->image3d.img, 0, 0);
    return (0);
}

int init_game(t_map *map)
{
    init_start(map);
    mlx_do_key_autorepeatoff(map->game.mlx);
    mlx_hook(map->game.window, 2, 1L << 0, &key_press, map);
    mlx_hook(map->game.window, 3, 1L << 1, &key_release, map);
    mlx_hook(map->game.window, 17, 1L << 17, &close_key, map);
    mlx_loop_hook(map->game.mlx, &ft_check, map);
    mlx_loop(map->game.mlx);
    return (1);
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