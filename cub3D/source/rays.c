/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:25:14 by zcherrad          #+#    #+#             */
/*   Updated: 2023/02/03 15:30:41 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * It draws the walls, floor, and ceiling
 * 
 * @param y the y coordinate of the top of the wall
 * @param x the x position of the wall
 * @param var the structure that contains all the variables
 */
void	drawing_rotation_angle(int y, int x, t_var *var)
{
	int	x1;
	int	y1;
	int	w;
	int	h;

	w = (var->player->wall_strip_width * TILE_SIZE) + x;
	h = (var->player->wall_strip_height * TILE_SIZE) + y;
	y1 = -1;
	while (++y1 < var->real_height)
	{
		x1 = x - 1;
		while (++x1 < w)
		{
			if ((y1 < (var->real_height) && y1 >= 0)
				&& (x1 < (var->real_width) && x1 >= 0))
			{
				if (y1 < y)
					drawing_ceil_floor(var, x1, y1, 1);
				else if (y1 >= y && y1 < h)
					drawing_wall(var, x1, y1, y);
				else if (y1 >= h)
					drawing_ceil_floor(var, x1, y1, 3);
			}
		}
	}
}

/**
 * It calculates the distance of the wall
 * from the player, and then draws the wall
 * 
 * @param var the structure that contains all the variables of the program.
 * @param old_d the distance from the player to the wall
 * @param i the current column of the screen
 * @param ray_angle the angle of the ray that is being casted
 */
void	render_wall(t_var *var, float old_d, int i, float ray_angle)
{
	float	current_d;
	float	distance_projection_plane;
	float	wall_strip_height;
	float	width_of_pixl;
	float	first_point_of_wall;

	current_d = cos(ray_angle - var->player->rotate_angle) \
		* old_d;
	distance_projection_plane = ((var->real_width / TILE_SIZE) / 2) \
		/ tan(var->player->fov_angle / 2);
	wall_strip_height = (TILE_SIZE / current_d) \
		* distance_projection_plane * 0.5 ;
	first_point_of_wall = (var->real_height / 2)
		- (wall_strip_height / 2) * TILE_SIZE;
	width_of_pixl = i * var->player->wall_strip_width * TILE_SIZE;
	var->player->wall_strip_height = wall_strip_height;
	drawing_rotation_angle(first_point_of_wall, width_of_pixl, var);
}

/**
 * It calculates the distance to the wall and renders it
 * 
 * @param var the main structure that contains all the information about the game
 */
void	project_plane_wall(t_var *var)
{
	float	ray_angle;
	int		i;
	t_ray	result;
	t_ray	hori_d;
	t_ray	vert_d;

	i = -1;
	ray_angle = var->player->rotate_angle - (var->player->fov_angle / 2);
	ray_angle = normalize(ray_angle);
	while (++i <= var->player->rays_num)
	{
		var->player->is_horz_intr = 1;
		hori_d = horizontal_intersection(var, ray_angle);
		vert_d = vertical_intersection(var, ray_angle);
		if (hori_d.distance > vert_d.distance)
		{
			result = vert_d;
			var->player->is_horz_intr = 0;
		}
		else
			result = hori_d;
		var->v = result;
		render_wall(var, result.distance, i, ray_angle);
		ray_angle += var->player->fov_angle / var->player->rays_num;
	}
}
