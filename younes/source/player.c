
#include "cub3D.h"

// this function get the obj_plyr.rotation_angle
// based on the player orientation p_orientation
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
	int	player_size;
	int	i;

	y = data->obj_plyr->minimap_size / 2;
	x = data->obj_plyr->minimap_size / 2;
	i = -1;
	player_size = data->obj_plyr->player_size;
	ft_draw_square(y, x, player_size, data);
}

// this function checks if there is a wall in the position map[new_y][new_x]
int	ft_is_in_wall(int new_x, int new_y, t_data *data)
{
	int	w;
	int	h;

	w = (data->obj_map->map_width) * COLUMN_SIZE;
	h = (data->obj_map->map_height) * COLUMN_SIZE;
	if (new_x < 0 || new_x > w || new_y < 0 || new_y > h)
		return (1);
	if (data->obj_map->map[new_y / COLUMN_SIZE][new_x / COLUMN_SIZE] == '1')
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
	t_player	*obj_plyr;

	obj_plyr = data->obj_plyr;
	if (key == KEY_AROW_R || key == KEY_AROW_L || key == KEY_D
		|| key == KEY_A || key == MOUSE_L || key == MOUSE_R
		|| key == MOUSE_L2 || key == MOUSE_R2)
	{
		obj_plyr->rotate_angle += obj_plyr->turn_direction \
		* obj_plyr->rotation_speed;
		obj_plyr->turn_direction = 0;
	}
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		move_step = obj_plyr->move_speed * obj_plyr->walk_direction;
		new_x = obj_plyr->x + move_step * cos(obj_plyr->rotate_angle);
		new_y = obj_plyr->y + move_step * sin(obj_plyr->rotate_angle);
		if (ft_is_in_wall(new_x, new_y, data) == 0)
		{
			obj_plyr->x = new_x;
			obj_plyr->y = new_y;
		}
	}
}
