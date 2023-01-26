
#include "cub3D.h"

// this function limits the angle between (0~360) degree or (0~2PI) radian
float   ft_normalize_angle(float angle)
{
    angle =  fmod(angle , 2 * M_PI);
    while (angle < 0)
        angle =  angle + (2 * M_PI);
    return (angle);
}

// this function for draw a ray
void    ft_draw_one_ray(int x, int y, float ray_angle, t_data *data)
{
    int line_lenght;
    int j;
    
    j = -1;
	line_lenght = 50;
    while (++j < line_lenght)
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + cos(ray_angle) * j,  y + sin(ray_angle) * j, 0x00FF0000);
}

// this function draw the player on the map
void ft_render_rays(t_data *data)
{
	int		y;
	int		x;
    float ray_angle;
	int i;

	y = data->obj_plyr->y * COLUMN_SIZE;
	x = data->obj_plyr->x * COLUMN_SIZE;
	i = -1;
    ray_angle = data->obj_plyr->rotation_angle - (data->obj_plyr->fov_angle / 2);
    ray_angle = ft_normalize_angle(ray_angle);
    printf("ray_angle  == %f\n", ray_angle);
    while (++i < data->obj_plyr->rays_num)
    {
        ft_draw_one_ray(x, y, ray_angle, data);
        ray_angle += data->obj_plyr->fov_angle / data->obj_plyr->rays_num;
    }
}