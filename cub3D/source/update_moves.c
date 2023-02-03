/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:52:02 by zcherrad          #+#    #+#             */
/*   Updated: 2023/02/03 14:25:46 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * It moves the player to the left
 * 
 * @param player the player struct
 * @param fixedangle The angle the player is facing, in radians.
 * @param new_x the new x position of the player
 * @param new_y the new y position of the player
 */
void	move_left(t_player *player, float fixedangle,
	float *new_x, float *new_y)
{
	*new_x = player->x + player->move_speed * cos(fixedangle);
	*new_y = player->y + player->move_speed * sin(fixedangle);
}

/**
 * It moves the player to the right
 * 
 * @param player the player struct
 * @param fixedangle The angle the player is facing.
 * @param new_x The new x position of the player
 * @param new_y the new y position of the player
 */
void	move_right(t_player *player, float fixedangle,
	float *new_x, float *new_y)
{
	*new_x = player->x + player->move_speed * cos(fixedangle);
	*new_y = player->y + player->move_speed * sin(fixedangle);
}

/**
 * 
 * 
 * @param player The player struct
 * @param x The x coordinate of the player.
 * @param y The y coordinate of the player.
 */
void	update_playe(t_player *player, float x, float y)
{
	player->x = x;
	player->y = y;
}

/**
 * It changes the player's angle based on the direction
 * they're turning and the speed at which they're
 * turning
 * 
 * @param player The player object.
 */
void	change_angle(t_player *player)
{
	player->rotate_angle = normalize(player->rotate_angle + \
		player->turn_direction * player->rotation_speed);
	player->turn_direction = 0;
}

/**
 * It calculates the new x and y coordinates of 
 * the player, based on the current x and y coordinates,
 * the move speed, the walking direction, and the rotation angle
 * 
 * @param player the player object
 * @param move_step the amount of movement that the player will make.
 * @param new_x the new x coordinate of the player
 * @param new_y The new y coordinate of the player after moving.
 */
void	change_x_y(t_player *player, float *move_step,
					float *new_x, float *new_y)
{
	*move_step = player->move_speed * player->walk_direction;
	*new_x = player->x + *move_step * cos(player->rotate_angle);
	*new_y = player->y + *move_step * sin(player->rotate_angle);
}
