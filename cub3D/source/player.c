/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:50:50 by yjarhbou          #+#    #+#             */
/*   Updated: 2023/02/03 17:50:52 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/**
 * It returns the angle of the direction the player is facing
 * 
 * @param c The character that represents the direction the player is facing.
 * 
 * @return The angle of the direction of the player.
 */
float	check_angle(char c)
{
	if (c == 'W')
		return (M_PI);
	else if (c == 'E')
		return (0);
	else if (c == 'N')
		return ((3 * M_PI) / 2);
	else if (c == 'S')
		return (M_PI / 2);
	return (0);
}

/**
 * It normalizes the angle of the player's rotation
 * 
 * @param isfront 1 = front, -1 = left, -2 = right, 0 = back
 * @param player the player
 * 
 * @return The angle of the player.
 */
float	ft_normalize_promax(int isfront, t_player *player)
{
	float	angle;

	if (isfront == 1)
		angle = normalize(player->rotate_angle);
	else if (isfront == -1)
		angle = normalize(player->rotate_angle - (M_PI / 2));
	else if (isfront == -2)
		angle = normalize(player->rotate_angle + (M_PI / 2));
	else if (isfront == 0)
		angle = normalize(player->rotate_angle + M_PI);
	else
		angle = normalize(player->rotate_angle);
	return (angle);
}

/**
 * It checks if the player is in a corner and if so, returns 1
 * 
 * @param x the x coordinate of the current ray
 * @param y the y coordinate of the current ray
 * @param var the structure containing all the variables
 * @param isfront 1 if the ray is in front of the player, 0 if it's behind.
 * 
 * @return the value of the variable "angle"
 */
int	ft_special_case(int x, int y, t_var *var, int isfront)
{
	t_player	*p;
	t_map		*map;
	float		angle;

	p = var->player;
	map = var->map;
	angle = ft_normalize_promax(isfront, p);
	if (angle >= 0 && (angle < M_PI / 2))
		if (map->map[y + 1][x] == '1' && map->map[y][x + 1] == '1')
			return (1);
	if (angle >= (M_PI / 2) && (angle < (M_PI)))
		if (map->map[y + 1][x] == '1' && map->map[y][x - 1] == '1')
			return (1);
	if (angle >= (M_PI) && (angle < (3 * M_PI / 2)))
		if (map->map[y - 1][x] == '1' && map->map[y][x - 1] == '1')
			return (1);
	if (angle >= (3 * M_PI / 2) && (angle < 2 * M_PI))
		if (map->map[y - 1][x] == '1' && map->map[y][x + 1] == '1')
			return (1);
	return (0);
}

/**
 * It checks if the player is going to hit a wall
 * 
 * @param new_x the new x position of the player
 * @param new_y the new y position of the player
 * @param var the main structure that contains all the information about the game
 * @param front 0 for left, 1 for right, 2 for up, 3 for down
 * 
 * @return a 1 if there is a wall, and a 0 if there is not.
 */
int	has_wall(int new_x, int new_y, t_var *var, int front)
{
	int	new_width;
	int	new_height;

	(void)front;
	new_width = (var->map->width) * TILE_SIZE;
	new_height = (var->map->height) * TILE_SIZE;
	if (new_x < 0 || new_x > new_width || new_y < 0 || new_y > new_height)
		return (1);
	if (var->map->map[new_y / TILE_SIZE][new_x / TILE_SIZE] != '0')
		return (1);
	if (var->map->map[new_y / TILE_SIZE][new_x / TILE_SIZE] != '0')
		return (1);
	if (ft_special_case(var->player->x / TILE_SIZE, \
		var->player->y / TILE_SIZE, var, front) == 1)
		return (1);
	else
		return (0);
}

/**
 * It checks if the player is trying to move, and if so,
 * it checks if there's a wall in the way. If
 * there isn't, it updates the player's position
 * 
 * @param var the main structure that contains all the information about the game
 * @param key the key that was pressed
 */
void	update(t_var *var, int key)
{
	float		move_step;
	float		new_x;
	float		new_y;
	t_player	*player;

	player = var->player;
	move_step = player->move_speed;
	if (key == KEY_A)
		move_left(player, player->rotate_angle - (M_PI / 2), &new_x, &new_y);
	else if (key == KEY_D)
		move_right(player, player->rotate_angle + (M_PI / 2), &new_x, &new_y);
	if ((key == KEY_A && has_wall(new_x, new_y, var, -1) == 0) || \
		(key == KEY_D && has_wall(new_x, new_y, var, -2) == 0))
		update_playe(player, new_x, new_y);
	else if (key == KEY_RIGHT || key == KEY_LEFT)
		change_angle(player);
	else if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		change_x_y(player, &move_step, &new_x, &new_y);
		if (key == KEY_W && has_wall(new_x, new_y, var, 1) == 0)
			update_playe(player, new_x, new_y);
		else if (key == KEY_S && has_wall(new_x, new_y, var, 0) == 0)
			update_playe(player, new_x, new_y);
	}
	var->map->map[(int)player->y / TILE_SIZE][(int)player->x / TILE_SIZE] = '0';
}
