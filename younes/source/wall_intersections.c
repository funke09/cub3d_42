

#include "cub3D.h"

typedef struct s_var
{
	float   x_intercept;
    float   y_intercept;
    float   x_steps;
    float   y_steps;
    
    int     is_ray_facing_up;
    int     is_ray_facing_down;
    int     is_ray_facing_right;
    int     is_ray_facing_left;

    float     next_horz_touch_x;
    float     next_horz_touch_y;
    int       found_horz_wall_hit;
    
    float     next_vertcl_touch_x;
    float     next_vertcl_touch_y;
    int     found_vertcl_wall_hit;
    
    int     x_wall_hit;
    int     y_wall_hit;
    int     window_w;
    int     window_h;
    float     distance;
} t_var;

// this function for know where the ray is facing 
void    ft_ray_facing(t_var *v, float ray_angle)
{
    v->is_ray_facing_up = 0;
    v->is_ray_facing_down = 0;
    v->is_ray_facing_right = 0;
    v->is_ray_facing_left = 0;
    if (ray_angle > M_PI && ray_angle < 2 * M_PI)
        v->is_ray_facing_up = 1;
    if (v->is_ray_facing_up == 0)
        v->is_ray_facing_down = 1;
    if (ray_angle > M_PI * 0.5 && ray_angle < 1.5 * M_PI)
        v->is_ray_facing_left = 1;
    if (v->is_ray_facing_left == 0)
        v->is_ray_facing_right = 1;
}

// this function initialize the ft_horizontal_intersection() function vars
void    ft_init_horz_vars(t_data *data, float ray_angle, t_var *v)
{
    v->y_intercept = floor(data->obj_plyr->y / COLUMN_SIZE) * COLUMN_SIZE;
    if (v->is_ray_facing_down == 1)
        v->y_intercept += COLUMN_SIZE;
    v->x_intercept = data->obj_plyr->x + ((v->y_intercept - data->obj_plyr->y) / tan(ray_angle));
    
    v->y_steps = COLUMN_SIZE;
    if (v->is_ray_facing_up == 1)
        v->y_steps *= -1;     
    v->x_steps = COLUMN_SIZE / tan(ray_angle);
    if (v->is_ray_facing_left == 1 && v->x_steps > 0)
        v->x_steps *= -1;
    if (v->is_ray_facing_right == 1 && v->x_steps < 0)
        v->x_steps *= -1;

    v->next_horz_touch_x = v->x_intercept;
    v->next_horz_touch_y = v->y_intercept;
    if (v->is_ray_facing_up == 1)
        v->next_horz_touch_y--;
    v->found_horz_wall_hit = 0;
    v->x_wall_hit = 0;
    v->y_wall_hit = 0;
    v->distance = sqrt(pow((v->y_intercept - data->obj_plyr->y), 2) + pow((v->y_intercept - data->obj_plyr->y) / tan(ray_angle), 2));
    v->window_w = data->obj_map->map_width * COLUMN_SIZE;
    v->window_h = data->obj_map->map_height * COLUMN_SIZE;
}

// this function return the distance between the player and the horizontal intersection with the wall
float    ft_horizontal_intersection(t_data *data, float ray_angle)
{
    t_var    v;

    ft_ray_facing(&v, ray_angle);
    ft_init_horz_vars(data, ray_angle, &v);    
    while (v.next_horz_touch_x >= 0 && v.next_horz_touch_x < v.window_w 
        && v.next_horz_touch_y >= 0 && v.next_horz_touch_y < v.window_h)
    {
        if (ft_is_in_wall(v.next_horz_touch_x, v.next_horz_touch_y, data) == 1)
        {
            v.found_horz_wall_hit = 1;
            v.x_wall_hit = v.next_horz_touch_x;
            v.y_wall_hit = v.next_horz_touch_y;
            return(v.distance);
        }
        else
        {
            v.next_horz_touch_x += v.x_steps;
            v.next_horz_touch_y += v.y_steps;
            v.distance += sqrt(pow(v.x_steps, 2) + pow(v.y_steps, 2));
        }
    }
    return(v.window_w * v.window_h);
}

// this function initialize the ft_vertical_intersection() function vars
void    ft_init_vertcl_vars(t_data *data, float ray_angle, t_var *v)
{
    v->x_intercept = floor(data->obj_plyr->x / COLUMN_SIZE) * COLUMN_SIZE;
    if (v->is_ray_facing_right == 1)
        v->x_intercept += COLUMN_SIZE;
    v->y_intercept = data->obj_plyr->y + ((v->x_intercept - data->obj_plyr->x) * tan(ray_angle));
    
    v->x_steps = COLUMN_SIZE;
    if (v->is_ray_facing_left == 1)
        v->x_steps *= -1;     
    v->y_steps = COLUMN_SIZE * tan(ray_angle);
    if (v->is_ray_facing_up == 1 && v->y_steps > 0)
        v->y_steps *= -1;
    if (v->is_ray_facing_down == 1 && v->y_steps < 0)
        v->y_steps *= -1;

    v->next_vertcl_touch_x = v->x_intercept;
    v->next_vertcl_touch_y = v->y_intercept;
    if (v->is_ray_facing_left == 1)
        v->next_vertcl_touch_x--;
    v->found_vertcl_wall_hit = 0;
    v->x_wall_hit = 0;
    v->y_wall_hit = 0;
    v->distance = sqrt(pow((v->x_intercept - data->obj_plyr->x), 2) + pow((v->x_intercept - data->obj_plyr->x) * tan(ray_angle), 2));
    v->window_w = data->obj_map->map_width * COLUMN_SIZE;
    v->window_h = data->obj_map->map_height * COLUMN_SIZE;
}

// this function return the distance between the player and the vertical intersection with the wall
float    ft_vertical_intersection(t_data *data, float ray_angle)
{
    t_var    v;

    ft_ray_facing(&v, ray_angle);
    ft_init_vertcl_vars(data, ray_angle, &v);    
    while (v.next_vertcl_touch_x >= 0 && v.next_vertcl_touch_x < v.window_w 
        && v.next_vertcl_touch_y >= 0 && v.next_vertcl_touch_y < v.window_h)
    {
        if (ft_is_in_wall(v.next_vertcl_touch_x, v.next_vertcl_touch_y, data) == 1)
        {
            v.found_vertcl_wall_hit = 1;
            v.x_wall_hit = v.next_vertcl_touch_x;
            v.y_wall_hit = v.next_vertcl_touch_y;
            return(v.distance);
        }
        else
        {
            v.next_vertcl_touch_x += v.x_steps;
            v.next_vertcl_touch_y += v.y_steps;
            v.distance += sqrt(pow(v.x_steps, 2) + pow(v.y_steps, 2));
        }
    }
    return(v.window_w * v.window_h);
}
