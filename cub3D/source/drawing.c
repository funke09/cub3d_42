/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:39:14 by zcherrad          #+#    #+#             */
/*   Updated: 2023/02/03 15:20:48 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/**
 * It sets the texture to be used for the wall
 * 
 * @param var the structure that contains all the information about the game.
 * @param x the x coordinate of the texture
 * @param image the image to draw
 */
void	which_textur(t_var *var, int *x, t_image **image)
{
	if (var->player->is_horz_intr == 1)
	{
		*x = (int)var->v.next_horz_touch_x % TEXTUR_WIDTH;
		if (var->player->is_ray_up == 1)
			*image = var->image->no_texture;
		if (var->player->is_ray_up == 0)
			*image = var->image->so_texture;
	}
	else
	{
		*x = (int)var->v.next_vertcl_touch_y % TEXTUR_WIDTH;
		if (var->player->is_ray_right == 0)
			*image = var->image->we_texture;
		if (var->player->is_ray_right == 1)
			*image = var->image->ea_texture;
	}
}

/**
 * It draws the wall
 * 
 * @param var the main structure
 * @param x the x coordinate of the pixel to be drawn
 * @param y the y coordinate of the pixel to be drawn
 * @param first_wall the first pixel of the wall to draw
 * 
 * @return the value of the pixel at the given coordinates.
 */
void	drawing_wall(t_var *var, int x, int y, int first_wall)
{
	t_image	*img;
	char	*dst;
	int		t_x;
	int		t_y;

	if (y >= (var->real_height)
		|| x >= (var->real_width))
		return ;
	which_textur(var, &t_x, &img);
	t_y = ((y - first_wall) * \
		(TEXTUR_WIDTH / (var->player->wall_strip_height * TILE_SIZE)));
	dst = var->img_var + (y * var->line_length + \
		x * (var->bits_per_pixel / 8));
	*(unsigned int *)dst = *(unsigned int *)&img->img_var[((t_y % TILE_SIZE) \
		* img->line_size + (t_x % TILE_SIZE) * (img->bits_per_pixel / 8))];
}

/**
 * It draws the ceiling and floor
 * 
 * @param var the structure that contains all the information about the game
 * @param x the x coordinate of the pixel to be drawn
 * @param y the y coordinate of the pixel to be drawn
 * @param color 1 = ceil, 3 = floor
 * 
 * @return the color of the pixel.
 */
void	drawing_ceil_floor(t_var *var, int x, int y, int color)
{
	char	*dst;

	if (y > (var->real_height)
		|| x > (var->real_width))
		return ;
	if (y >= (var->real_height)
		|| x >= (var->real_width))
		return ;
	dst = var->img_var + \
		(y * var->line_length + x * (var->bits_per_pixel / 8));
	if (color == 1)
		*(unsigned int *)dst = var->map->ceil_color_dc;
	else if (color == 3)
		*(unsigned int *)dst = var->map->floor_color_dc;
}
