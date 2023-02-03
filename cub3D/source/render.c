/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:36:13 by yjarhbou          #+#    #+#             */
/*   Updated: 2023/02/03 17:36:16 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * It initializes the textures
 * that are used in the game
 * 
 * @param var a pointer to the structure that 
 * contains all the information about the game.
 * @param number the number of the texture (1-4)
 * @param path the path to the texture file
 */
void	init_texturs_utile(t_var *var, int number, char *path)
{
	void	*ptr;
	int		s;
	t_image	*texture;

	ptr = var->mlx_ptr;
	texture = (t_image *)malloc(sizeof(t_image));
	texture->ptr = mlx_xpm_file_to_image(ptr, path, &s, &s);
	if (!texture->ptr)
	{
		destroy_textures(var);
		error_map(var, 5);
	}
	texture->img_var = mlx_get_data_addr(texture->ptr, \
	&texture->bits_per_pixel, &texture->line_size, &texture->endian);
	if (number == 1)
		var->image->ea_texture = texture;
	else if (number == 2)
		var->image->we_texture = texture;
	else if (number == 3)
		var->image->no_texture = texture;
	else if (number == 4)
		var->image->so_texture = texture;
}

/**
 * It initializes the textures
 * 
 * @param var the structure that contains all the variables
 */
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

/**
 * It updates the player's position and direction,
 * then projects the walls onto the screen
 * 
 * @param var the structure containing all the variables
 * @param key the key that was pressed
 */
void	render(t_var *var, int key)
{
	update(var, key);
	project_plane_wall(var);
}
