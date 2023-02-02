
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
 * It checks if the player is going to hit a wall
 * 
 * @param new_x the new x position of the player
 * @param new_y the new y position of the player
 * @param var the structure that contains all the variables
 * 
 * @return the value of the map at the given coordinates.
 */
int	has_wall(int new_x, int new_y, t_var *var)
{
	int	w;
	int	h;

	w = (var->map->width) * TILE_SIZE;
	h = (var->map->height) * TILE_SIZE;
	if (new_x < 0 || new_x > w || new_y < 0 || new_y > h)
		return (1);
	if (var->map->map[new_y / TILE_SIZE][new_x / TILE_SIZE] != '0')
		return (1);
	if (var->map->map[new_y / TILE_SIZE][new_x / TILE_SIZE] != '0')
		return (1);
	else
		return (0);
}

/**
 * It checks if the player is in a corner and if so, it returns 1
 * 
 * @param x the x coordinate of the player
 * @param y the y coordinate of the player
 * @param var the structure that contains all the variables
 * @param isfront 1 if the ray is in front of the player, 0 if it's behind
 */
int	ft_special_case(int x, int y, t_var *var, int isfront)
{
	t_player *p;
	t_map *map;
	float angle;
	p = var->player;
	map = var->map;
	if (isfront == 1)
		angle = normalize(p->rotate_angle);
	else if (isfront == -1)
		angle = normalize(p->rotate_angle - (M_PI / 2));
	else if (isfront == -2)
		angle = normalize(p->rotate_angle + (M_PI / 2));
	else 
		angle = normalize(p->rotate_angle + M_PI);
	printf("rotate_angle %f \n", angle);
	if (angle >= 0 && (angle < M_PI / 2))
	{
		printf("ft_special_case1 \n");
		if ( map->map[y + 1][x] == '1' && map->map[y][x + 1] == '1')
			return (1);
	}
	else if (angle >= (M_PI/2) && (angle <= (M_PI)))
	{
			if ( map->map[y + 1][x] == '1' && map->map[y][x - 1] == '1')
			return (1);
	}
	else if (angle >= (M_PI) && (angle < (3 * M_PI / 2)))
	{
			if ( map->map[y - 1][x] == '1' && map->map[y][x - 1] == '1')
			return (1);
	}
	else if (angle >= (3 * M_PI / 2) && (angle <= 2 * M_PI))
	{
		if ( map->map[y - 1][x] == '1' && map->map[y][x + 1] == '1')
			return (1);
	}
	return (0);
}

/**
 * It updates the player's position based on the key pressed
 * 
 * @param var the structure that contains all the information about the game
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
	if (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_D
		|| key == KEY_A )
	{
		if( key == KEY_A)
		{
			new_x = player->x + move_step * cos(player->rotate_angle - (M_PI / 2));
			new_y = player->y + move_step * sin(player->rotate_angle - (M_PI / 2));
		}else if ( key == KEY_D)
		{
			new_x = player->x + move_step * cos(player->rotate_angle + (M_PI / 2));
			new_y = player->y + move_step * sin(player->rotate_angle + (M_PI / 2));
		}
		if (key == KEY_A && has_wall(new_x, new_y, var) == 0 && ft_special_case(player->x, player->y, var, -1) == 0)
		{	player->x = new_x;
			player->y = new_y;
		}
		else if(key == KEY_D && has_wall(new_x, new_y, var) == 0 && ft_special_case(player->x, player->y, var, -2) == 0)
		{
			player->x = new_x;
			player->y = new_y;
		}
		else if ( key == KEY_RIGHT || key == KEY_LEFT)
		{
			player->rotate_angle += player->turn_direction \
			* player->rotation_speed;
			player->turn_direction = 0;
		}
	}
	if (key == KEY_W || key == KEY_S)
	{
		move_step = player->move_speed * player->walk_direction;
		new_x = player->x + move_step * cos(player->rotate_angle);
		new_y = player->y + move_step * sin(player->rotate_angle);
		if (key == KEY_W && has_wall(new_x, new_y, var) == 0  && ft_special_case(player->x / TILE_SIZE, player->y / TILE_SIZE, var, 1) == 0)
		{
			player->x = new_x;
			player->y = new_y;
		}
		else if ( key == KEY_S && has_wall(new_x, new_y, var) == 0  && ft_special_case(player->x / TILE_SIZE, player->y / TILE_SIZE, var, 0) == 0)
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
	var->map->map[(int)player->y/TILE_SIZE][(int)player->x/TILE_SIZE]  = '0';
}
