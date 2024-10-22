
#include "cub3D.h"

// this function get the player.rotation_angle
// based on the player orientation player_derection
float	ft_get_rot_angle(char c)
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
void	ft_render_player(t_data *data)
{
	int	y;
	int	x;
	int	sizeofplayer;
	int	i;

	y = data->player->minimap_size / 2;
	x = data->player->minimap_size / 2;
	i = -1;
	sizeofplayer = data->player->sizeofplayer;
	ft_draw_square(y, x, sizeofplayer, data);
}

// this function checks if there is a wall in the position map[new_y][new_x]
int	ft_is_in_wall(int new_x, int new_y, t_data *data)
{
	int	w;
	int	h;

	w = (data->map->width) * TILE_SIZE;
	h = (data->map->height) * TILE_SIZE;
	if (new_x < 0 || new_x > w || new_y < 0 || new_y > h)
		return (1);
	if (data->map->map[new_y / TILE_SIZE][new_x / TILE_SIZE] == '1')
		return (1);
	else
		return (0);
}

// this function updates the players info based on the key you pressed
void	ft_update(t_data *data, int key)
{
	float		move_step;
	float		new_x;
	float		new_y;
	t_player	*player;

	player = data->player;
	if (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_D
		|| key == KEY_A || key == MOUSE_L || key == MOUSE_R
		|| key == MOUSE_L2 || key == MOUSE_R2)
	{
		player->rotate_angle += player->turn_direction \
		* player->rotation_speed;
		player->turn_direction = 0;
	}
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		move_step = player->move_speed * player->walk_direction;
		new_x = player->x + move_step * cos(player->rotate_angle);
		new_y = player->y + move_step * sin(player->rotate_angle);
		if (ft_is_in_wall(new_x, new_y, data) == 0)
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
}
