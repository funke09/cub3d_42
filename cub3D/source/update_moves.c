/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:52:02 by zcherrad          #+#    #+#             */
/*   Updated: 2023/02/03 02:58:23 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_left(t_player *player, float fixedangle,
	float *new_x, float *new_y)
{
	*new_x = player->x + player->move_speed * cos(fixedangle);
	*new_y = player->y + player->move_speed * sin(fixedangle);
}

void	move_right(t_player *player, float fixedangle,
	float *new_x, float *new_y)
{
	*new_x = player->x + player->move_speed * cos(fixedangle);
	*new_y = player->y + player->move_speed * sin(fixedangle);
}

void	update_playe(t_player *player, float x, float y)
{
	player->x = x;
	player->y = y;
}

void	change_angle(t_player *player)
{
	player->rotate_angle = normalize(player->rotate_angle + \
		player->turn_direction * player->rotation_speed);
	player->turn_direction = 0;
}

void	change_x_y(t_player *player, float *move_step,
					float *new_x, float *new_y)
{
	*move_step = player->move_speed * player->walk_direction;
	*new_x = player->x + *move_step * cos(player->rotate_angle);
	*new_y = player->y + *move_step * sin(player->rotate_angle);
}
