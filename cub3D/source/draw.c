
#include "cub3D.h"

void	ft_mlx_wall_body(t_data *data, int *offsetx, t_image **tmp)
{
	if (data->player->is_horz_intr == 1)
	{
		*offsetx = (int)data->v.next_horz_touch_x % TEXTUR_WIDTH;
		if (data->player->is_ray_up == 1)
			*tmp = data->image->no_texture;
		if (data->player->is_ray_up == 0)
			*tmp = data->image->so_texture;
	}
	else
	{
		*offsetx = (int)data->v.next_vertcl_touch_y % TEXTUR_WIDTH;
		if (data->player->is_ray_right == 0)
			*tmp = data->image->we_texture;
		if (data->player->is_ray_right == 1)
			*tmp = data->image->ea_texture;
	}
}

// this function draw a pixel without the scale factor
void	my_mlx_pixel_put_wall(t_data *data, int x, int y, int wall_top)
{
	char	*dst;
	t_image	*tmp;
	int		s;
	int		offsetx;
	int		offsety;

	s = TILE_SIZE;
	if (y > (data->real_height)
		|| x > (data->real_width))
		return ;
	if (y >= (data->real_height)
		|| x >= (data->real_width))
		return ;
	ft_mlx_wall_body(data, &offsetx, &tmp);
	offsety = ((y - wall_top) * \
		(TEXTUR_WIDTH / (data->player->wall_strip_height * TILE_SIZE)));
	dst = data->img_data + (y * data->line_length + \
		x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = *(unsigned int *)&tmp->img_data[((offsety % s) \
		* tmp->line_size + (offsetx % s) * (tmp->bits_per_pixel / 8))];
}

// this function draw a pixel without the scale factor
void	my_mlx_pixel_put2(t_data *data, int x, int y, int color_num)
{
	char	*dst;
	int		s;

	s = TILE_SIZE;
	if (y > (data->real_height)
		|| x > (data->real_width))
		return ;
	if (y >= (data->real_height)
		|| x >= (data->real_width))
		return ;
	dst = data->img_data + \
		(y * data->line_length + x * (data->bits_per_pixel / 8));
	if (color_num == 1)
		*(unsigned int *)dst = data->map->ceil_color_dc;
	else if (color_num == 3)
		*(unsigned int *)dst = data->map->floor_color_dc;
}

// this function draws a square on the position map[y][x] 
// with a size of your choice
void	ft_draw_square(int y, int x, int size, t_data *data)
{
	int	h;
	int	w;

	y = y - size / 2;
	x = x - size / 2;
	h = y + size;
	w = x + size;
	while (y < h)
	{
		x = w - size;
		while (x < w)
		{
			my_mlx_pixel_put(data, x, y, 0x00ff000);
			x++;
		}
		y++;
	}
}

// this function for draw a ray
void	ft_draw_one_ray(t_data *data, float ray_angle, int size)
{
	int	j;

	j = -1;
	while (++j < size)
	{
		my_mlx_pixel_put(data, (data->player->x + cos(ray_angle) * j), \
		(data->player->y + sin(ray_angle) * j), 0x00FF0000);
	}
}
