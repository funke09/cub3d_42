/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:35:03 by zcherrad          #+#    #+#             */
/*   Updated: 2023/02/03 02:48:57 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/**
 * It frees the memory allocated for the map,
 * destroys the window, and exits the program
 *  ESC or X button
 * @param n_var a void pointer to the t_var struct
 */
int	ft_destroy_window(void *n_var)
{
	t_var	*var;
	int		i;

	var = (t_var *)n_var;
	i = -1;
	while (var->map->map[++i] != NULL)
		free(var->map->map[i]);
	free(var->map->map);
	mlx_destroy_window(var->mlx_ptr, var->win_ptr);
	exit(0);
}

void	key_press_2(t_var *var, int key)
{
	if (key == KEY_RIGHT || key == KEY_D)
	{
		var->player->walk_direction = 0;
		var->player->turn_direction = 1;
	}
	else if (key == KEY_LEFT || key == KEY_A)
	{
		var->player->walk_direction = 0;
		var->player->turn_direction = -1;
	}
}

/**
 * It takes the key pressed and the variable 
 * struct as arguments, and then it changes the player's
 * direction based on the key pressed
 * 
 * @param key the key that was pressed
 * @param n_var This is a void pointer to the 
 * variable that we passed to mlx_hook.
 * 
 * @return 0
 */
int	key_press(int key, void *n_var)
{
	t_var	*var;

	var = (t_var *) n_var;
	if (key == KEY_ESC)
		ft_destroy_window(var);
	else if (key == KEY_W)
	{
		var->player->turn_direction = 0;
		var->player->walk_direction = 1;
	}
	else if (key == KEY_S)
	{
		var->player->turn_direction = 0;
		var->player->walk_direction = -1;
	}
	else
		key_press_2(var, key);
	render(var, key);
	mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, var->img, 0, 0);
	return (0);
}
