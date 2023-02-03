
#include "cub3D.h"

void	ft_mlx_wall_body(t_var *var, int *offsetx, t_image **tmp)
{
	if (var->player->is_horz_intr == 1)
	{
		*offsetx = (int)var->v.next_horz_touch_x % TEXTUR_WIDTH;
		if (var->player->is_ray_up == 1)
			*tmp = var->image->no_texture;
		if (var->player->is_ray_up == 0)
			*tmp = var->image->so_texture;
	}
	else
	{
		*offsetx = (int)var->v.next_vertcl_touch_y % TEXTUR_WIDTH;
		if (var->player->is_ray_right == 0)
			*tmp = var->image->we_texture;
		if (var->player->is_ray_right == 1)
			*tmp = var->image->ea_texture;
	}
}

// this function draw a pixel without the scale factor
void	drawing_wall(t_var *var, int x, int y, int wall_top)
{
	char	*dst;
	t_image	*tmp;
	int		s;
	int		offsetx;
	int		offsety;

	s = TILE_SIZE;
	if (y > (var->real_height)
		|| x > (var->real_width))
		return ;
	if (y >= (var->real_height)
		|| x >= (var->real_width))
		return ;
	ft_mlx_wall_body(var, &offsetx, &tmp);
	offsety = ((y - wall_top) * \
		(TEXTUR_WIDTH / (var->player->wall_strip_height * TILE_SIZE)));
	dst = var->img_var + (y * var->line_length + \
		x * (var->bits_per_pixel / 8));
	*(unsigned int *)dst = *(unsigned int *)&tmp->img_var[((offsety % s) \
		* tmp->line_size + (offsetx % s) * (tmp->bits_per_pixel / 8))];
}

// this function draw a pixel without the scale factor
void	drawing_ceil_floor(t_var *var, int x, int y, int color_num)
{
	char	*dst;
	int		s;

	s = TILE_SIZE;
	if (y > (var->real_height)
		|| x > (var->real_width))
		return ;
	if (y >= (var->real_height)
		|| x >= (var->real_width))
		return ;
	dst = var->img_var + \
		(y * var->line_length + x * (var->bits_per_pixel / 8));
	if (color_num == 1)
		*(unsigned int *)dst = var->map->ceil_color_dc;
	else if (color_num == 3)
		*(unsigned int *)dst = var->map->floor_color_dc;
}

