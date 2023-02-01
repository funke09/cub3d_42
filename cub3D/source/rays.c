
#include "cub3D.h"

void	draw_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		x_scaled;
	int		y_scaled;
	float	scale_factor;
	int		minimap_end;

	if (y > (data->map->height * TILE_SIZE)
		|| x > (data->map->width * TILE_SIZE))
		return ;
	scale_factor = data->player->minimap_scale_factor;
	x_scaled = x * scale_factor;
	y_scaled = y * scale_factor;
	minimap_end = (data->player->minimap_size - 1) * scale_factor;
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

	w = (data->player->wall_strip_width * TILE_SIZE) + x;
	h = (data->player->wall_strip_height * TILE_SIZE) + y;
	y1 = -1;
	while (++y1 < data->real_height)
	{
		x1 = x - 1;
		while (++x1 < w)
		{
			if ((y1 < (data->real_height) && y1 >= 0)
				&& (x1 < (data->real_width) && x1 >= 0))
			{
				if (y1 < y)
					drawing_ceil_floor(data, x1, y1, 1);
				else if (y1 >= y && y1 < h)
					drawing_wall(data, x1, y1, y);
				else if (y1 >= h)
					drawing_ceil_floor(data, x1, y1, 3);
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

	correct_distance = cos(ray_angle - data->player->rotate_angle) \
		* bad_distnc;
	distance_projection_plane = ((data->real_width / TILE_SIZE) / 2) \
		/ tan(data->player->fov_angle / 2);
	wall_strip_height = (TILE_SIZE / correct_distance) \
		* distance_projection_plane * 0.5 ;
	y = (data->real_height / 2) - (wall_strip_height / 2) * TILE_SIZE;
	x = i * data->player->wall_strip_width * TILE_SIZE;
	data->player->wall_strip_height = wall_strip_height;
	ft_draw_rectangle(y, x, data);
}

// this function draw the rays on the minimap
void	render_rays(t_data *data)
{
	float	ray_angle;
	int		i;
	t_ray	result;
	t_ray	d1;
	t_ray	d2;

	i = -1;
	ray_angle = data->player->rotate_angle - (data->player->fov_angle / 2);
	ray_angle = normalize(ray_angle);
	while (++i < data->player->rays_num)
	{
		data->player->is_horz_intr = 1;
		d1 = horizontal_intersection(data, ray_angle);
		d2 = vertical_intersection(data, ray_angle);
		if (d1.distance > d2.distance)
		{
			result = d2;
			data->player->is_horz_intr = 0;
		}
		else
			result = d1;
		data->v = result;
		put_one_ray(data, ray_angle, result.distance);
		ray_angle += data->player->fov_angle / data->player->rays_num;
	}
}

// this function project the walls 
void	project_plane_wall(t_data *data)
{
	float	ray_angle;
	int		i;
	t_ray	result;
	t_ray	d1;
	t_ray	d2;

	i = -1;
	ray_angle = data->player->rotate_angle - (data->player->fov_angle / 2);
	ray_angle = normalize(ray_angle);
	while (++i < data->player->rays_num)
	{
		data->player->is_horz_intr = 1;
		d1 = horizontal_intersection(data, ray_angle);
		d2 = vertical_intersection(data, ray_angle);
		if (d1.distance > d2.distance)
		{
			result = d2;
			data->player->is_horz_intr = 0;
		}
		else
			result = d1;
		data->v = result;
		ft_render_wall(data, result.distance, i, ray_angle);
		ray_angle += data->player->fov_angle / data->player->rays_num;
	}
}
