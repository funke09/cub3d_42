/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:25:02 by zcherrad          #+#    #+#             */
/*   Updated: 2023/02/03 02:36:07 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_texturs_utile(t_var *var, int txtr_nbr, char *txtr_path)
{
	void	*p;
	int		s;
	t_image	*texture;

	p = var->mlx_ptr;
	texture = (t_image *)malloc(sizeof(t_image));
	texture->ptr = mlx_xpm_file_to_image(p, txtr_path, &s, &s);
	if (!texture->ptr)
	{
		destroy_textures(var);
		error_map(var, 5);
	}
	texture->img_var = mlx_get_data_addr(texture->ptr, \
	&texture->bits_per_pixel, &texture->line_size, &texture->endian);
	if (txtr_nbr == 1)
		var->image->ea_texture = texture;
	else if (txtr_nbr == 2)
		var->image->we_texture = texture;
	else if (txtr_nbr == 3)
		var->image->no_texture = texture;
	else if (txtr_nbr == 4)
		var->image->so_texture = texture;
}

void	init_texturs(t_var *var)
{
	t_img	*image;
	t_map	*map;

	image = var->image;
	map = var->map;
	init_texturs_utile(var, 1, map->ea_texture);
	init_texturs_utile(var, 2, map->we_texture);
	init_texturs_utile(var, 3, map->no_texture);
	init_texturs_utile(var, 4, map->so_texture);
}

void	render(t_var *var, int key)
{
	update(var, key);
	project_plane_wall(var);
}
