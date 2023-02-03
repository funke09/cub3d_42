/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:39:33 by zcherrad          #+#    #+#             */
/*   Updated: 2023/02/03 02:45:53 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/**
 * It initializes the player's
 * variables
 * 
 * @param player the player object
 * @param var a pointer to the main structure that contains all the variables.
 */
void	init_player(t_player *player, t_var *var)
{
	int	width;

	width = var->map->width;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotate_angle = check_angle(var->player->player_derection);
	player->move_speed = 30;
	player->rotation_speed = 10 * (M_PI / 180);
	player->fov_angle = 60 * (M_PI / 180);
	player->wall_strip_width = 0.1;
	player->rays_num = (var->real_width / TILE_SIZE) \
		/ player->wall_strip_width;
	player->sizeofplayer = 30;
}

/**
 * It initializes the mlx window,
 * creates the image, and renders the image to the window
 * 
 * @param var a pointer to the t_var structure
 */
void	ft_var_init(t_var *var)
{
	var->mlx_ptr = mlx_init();
	var->win_ptr = \
		mlx_new_window(var->mlx_ptr, var->real_width,
			var->real_height, "NAZISM");
	var->img = mlx_new_image(var->mlx_ptr, var->real_width,
			var->real_height);
	var->img_var = mlx_get_data_addr(var->img, &var->bits_per_pixel, \
	&var->line_length, &var->endian);
	init_texturs(var);
	render(var, RANDOM_KEY);
	mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, var->img, 0, 0);
}

/**
 * It initializes the map, the player,
 * the image, the window, and the mlx, and then it hooks the
 * key_press function to the window, the destroy_window
 * function to the window, and the mlx_loop to the
 * mlx
 * 
 * @param ac argument count
 * @param av the array of arguments passed to the program
 */
int	main(int ac, char **av)
{
	t_var		var;
	t_map		map;
	t_img		image;
	t_player	player;

	if (ac == 2)
	{
		var.map = &map;
		var.image = &image;
		var.player = &player;
		var.real_height = 1000;
		var.real_width = 2000;
		init_map(av[1], &var);
		init_player(&player, &var);
		ft_var_init(&var);
		mlx_hook(var.win_ptr, 02, 0, key_press, &var);
		mlx_hook(var.win_ptr, 17, 0, ft_destroy_window, &var);
		mlx_loop(var.mlx_ptr);
	}
	else
		printf("=> USAGE : ./cub3D [mapName.cub]\n");
}
