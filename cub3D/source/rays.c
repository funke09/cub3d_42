
#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		x_scaled;
	int		y_scaled;
	float	scale_factor;
	int		minimap_end;

	if (y > (data->obj_map->map_height * COLUMN_SIZE)
		|| x > (data->obj_map->map_width * COLUMN_SIZE))
		return ;
	scale_factor = data->obj_plyr->minimap_scale_factor;
	x_scaled = x * scale_factor;
	y_scaled = y * scale_factor;
	minimap_end = (data->obj_plyr->minimap_size - 1) * scale_factor;
	dst = data->img_data + (y_scaled * data->line_length + x_scaled \
		* (data->bits_per_pixel / 8));
	if (x_scaled == 0 || y_scaled == 0 || \
		x_scaled == minimap_end || y_scaled == minimap_end)
		*(unsigned int *)dst = 0x10ffff;
	else
		*(unsigned int *)dst = color;
}

// this function draws a rectange on the position 
// map[y][x] with a size of your choice
void	ft_draw_rectangle(int y, int x, t_data *data)
{
	int	x1;
	int	y1;
	int	w;
	int	h;

	w = (data->obj_plyr->wall_strip_width * COLUMN_SIZE) + x;
	h = (data->obj_plyr->wall_strip_height * COLUMN_SIZE) + y;
	y1 = -1;
	while (++y1 < data->fix_h)
	{
		x1 = x - 1;
		while (++x1 < w)
		{
			if ((y1 < (data->fix_h) && y1 >= 0)
				&& (x1 < (data->fix_w) && x1 >= 0))
			{
				if (y1 < y)
					my_mlx_pixel_put2(data, x1, y1, 1);
				else if (y1 >= y && y1 < h)
					my_mlx_pixel_put_wall(data, x1, y1, y);
				else if (y1 >= h)
					my_mlx_pixel_put2(data, x1, y1, 3);
			}
		}
	}
}

// this function will render a 3D projected wall 
// bad_distnc: is the distorted distance
void	ft_render_wall(t_data *data, float bad_distnc, int i, float ray_angle)
{
	float	distance_projection_plane;
	float	wall_strip_height;
	float	x;
	float	y;
	float	correct_distance;

	correct_distance = cos(ray_angle - data->obj_plyr->rotate_angle) \
		* bad_distnc;
	distance_projection_plane = ((data->fix_w / COLUMN_SIZE) / 2) \
		/ tan(data->obj_plyr->fov_angle / 2);
	wall_strip_height = (COLUMN_SIZE / correct_distance) \
		* distance_projection_plane * 0.5 ;
	y = (data->fix_h / 2) - (wall_strip_height / 2) * COLUMN_SIZE;
	x = i * data->obj_plyr->wall_strip_width * COLUMN_SIZE;
	data->obj_plyr->wall_strip_height = wall_strip_height;
	ft_draw_rectangle(y, x, data);
}

// this function draw the rays on the minimap
void	ft_render_rays(t_data *data)
{
	float	ray_angle;
	int		i;
	t_var	result;
	t_var	d1;
	t_var	d2;

	i = -1;
	ray_angle = data->obj_plyr->rotate_angle - (data->obj_plyr->fov_angle / 2);
	ray_angle = ft_normalize_angle(ray_angle);
	while (++i < data->obj_plyr->rays_num)
	{
		data->obj_plyr->is_horz_intr = 1;
		d1 = ft_horizontal_intersection(data, ray_angle);
		d2 = ft_vertical_intersection(data, ray_angle);
		if (d1.distance > d2.distance)
		{
			result = d2;
			data->obj_plyr->is_horz_intr = 0;
		}
		else
			result = d1;
		data->v = result;
		ft_draw_one_ray(data, ray_angle, result.distance);
		ray_angle += data->obj_plyr->fov_angle / data->obj_plyr->rays_num;
	}
}

// this function project the walls 
void	ft_project_walls(t_data *data)
{
	float	ray_angle;
	int		i;
	t_var	result;
	t_var	d1;
	t_var	d2;

	i = -1;
	ray_angle = data->obj_plyr->rotate_angle - (data->obj_plyr->fov_angle / 2);
	ray_angle = ft_normalize_angle(ray_angle);
	while (++i < data->obj_plyr->rays_num)
	{
		data->obj_plyr->is_horz_intr = 1;
		d1 = ft_horizontal_intersection(data, ray_angle);
		d2 = ft_vertical_intersection(data, ray_angle);
		if (d1.distance > d2.distance)
		{
			result = d2;
			data->obj_plyr->is_horz_intr = 0;
		}
		else
			result = d1;
		data->v = result;
		ft_render_wall(data, result.distance, i, ray_angle);
		ray_angle += data->obj_plyr->fov_angle / data->obj_plyr->rays_num;
	}
}
