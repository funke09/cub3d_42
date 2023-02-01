
#include "cub3D.h"

// this function get the player.rotation_angle
// based on the player orientation player_derection
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

// this function draw the player on the map
void	player_rendr(t_var *var)
{
	int	y;
	int	x;
	int	sizeofplayer;
	int	i;

	y = var->player->minimap_size / 2;
	x = var->player->minimap_size / 2;
	i = -1;
	sizeofplayer = var->player->sizeofplayer;
	draw_square(y, x, sizeofplayer, var);
}

// this function checks if there is a wall in the position map[new_y][new_x]
int	has_wall(int new_x, int new_y, t_var *var)
{
	int	w;
	int	h;

	w = (var->map->width) * TILE_SIZE;
	h = (var->map->height) * TILE_SIZE;
	if (new_x < 0 || new_x > w || new_y < 0 || new_y > h)
		return (1);
	if (var->map->map[new_y / TILE_SIZE][new_x / TILE_SIZE] == '1')
		return (1);
	else
		return (0);
}

// this function updates the players info based on the key you pressed
void	update(t_var *var, int key)
{
	float		move_step;
	float		new_x;
	float		new_y;
	t_player	*player;

	player = var->player;
	if (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_D
		|| key == KEY_A )
	{
		if(key == KEY_A)
		{
		move_step = player->move_speed;
		new_x = player->x + move_step * cos(player->rotate_angle - (M_PI / 2));
		new_y = player->y + move_step * sin(player->rotate_angle - (M_PI / 2));
		if (has_wall(new_x, new_y, var) == 0)
		{
			player->x = new_x;
			player->y = new_y;
		}
		}
		else if(key == KEY_D)
		{
		move_step = player->move_speed;
		new_x = player->x + move_step * cos(player->rotate_angle + (M_PI / 2));
		new_y = player->y + move_step * sin(player->rotate_angle + (M_PI / 2));
		if (has_wall(new_x, new_y, var) == 0)
		{
			player->x = new_x;
			player->y = new_y;
		}
		}
		else
		{
			player->rotate_angle += player->turn_direction \
			* player->rotation_speed;
			player->turn_direction = 0;
		}

	}
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		move_step = player->move_speed * player->walk_direction;
		new_x = player->x + move_step * cos(player->rotate_angle);
		new_y = player->y + move_step * sin(player->rotate_angle);
		if (has_wall(new_x, new_y, var) == 0)
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
}
