
#include "cub3D.h"

void ft_draw_square(int y, int x, int size, t_data *data)
{
	int h;
	int w;

	y = y - size / 2;
	x = x - size / 2;
	h = y + size;
	w = x + size;
	while (y < h)
	{
		x = w - size;
		while (x < w)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x,  y , 0x00e9eae0);
			x++;
		}
		y++;
	}
}

void ft_render_player(t_data *data)
{
	int		y;
	int		x;
	int player_size;
	int i;

	y = data->obj_plyr->y * COLUMN_SIZE;
	x = data->obj_plyr->x * COLUMN_SIZE;

	i = -1;
	player_size = 30;
	while (++i < player_size)
	{
		ft_draw_square(y, x, 10, data);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + cos(data->obj_plyr->rotation_angle) * i,  y + sin(data->obj_plyr->rotation_angle) * i, 0x00FF0000);
	}
}

int	ft_is_in_wall(int new_x, int new_y, t_data *data)
{
	if (new_x < 0 || new_x > data->obj_map->map_height + 1 || new_y < 0 || new_x > data->obj_map->map_width + 1)
		return (1);
	if (data->obj_map->map[new_y][new_x] == '1')
		return (1);
	else
		return (0);
}

void	ft_update(t_data *data, int key)
{
	float move_step;
	float	new_x;
	float	new_y;
	
	if (key == KEY_AROW_R || key == KEY_AROW_L || key == KEY_D || key == KEY_A)
	{
		data->obj_plyr->rotation_angle += data->obj_plyr->turn_direction * data->obj_plyr->rotation_speed;
		printf("1- data->obj_plyr->rotation_angle = %f\n", data->obj_plyr->rotation_angle);
		data->obj_plyr->turn_direction = 0;
	}
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D || key == KEY_D || key == KEY_A)
	{
		// printf("->walk_direction = %f\n", data->obj_plyr->walk_direction);
		move_step = data->obj_plyr->move_speed * data->obj_plyr->walk_direction;
		// printf("2- data->obj_plyr->rotation_angle = %f\n", data->obj_plyr->rotation_angle);
		// printf("1->data->obj_plyr->x = %f\n", data->obj_plyr->x);
		new_x = data->obj_plyr->x + move_step * cos(data->obj_plyr->rotation_angle);
		// data->obj_plyr->x += move_step * cos(data->obj_plyr->rotation_angle);
		// printf("2->data->obj_plyr->x = %f\n", move_step * cos(data->obj_plyr->rotation_angle));
		new_y = data->obj_plyr->y + move_step * sin(data->obj_plyr->rotation_angle);
		// data->obj_plyr->y += move_step * sin(data->obj_plyr->rotation_angle);
		if (ft_is_in_wall(new_x, new_y, data) == 0)
		{
			data->obj_plyr->x = new_x;
			data->obj_plyr->y = new_y;
		}
		
	}
	
}

int	ft_exit_handler(void *n_data)
{
	t_data	*data;
	int		i;

	data = (t_data *) n_data;
	i = -1;
	while (data->obj_map->map[++i] != NULL)
	{
		free(data->obj_map->map[i]);
		data->obj_map->map[i] = NULL;
	}
	free(data->obj_map->map);
	data->obj_map->map = NULL;
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}

int	ft_key_handler(int key, void *n_data)
{
	t_data	*data;
	char	**map;

	data = (t_data *) n_data;
	map = data->obj_map->map;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	if (key == KEY_ESC)
		ft_exit_handler(data);
	else if (key == KEY_W)
		data->obj_plyr->walk_direction = 1;
	else if (key == KEY_S)
		data->obj_plyr->walk_direction = -1;
	else if (key == KEY_AROW_R || key == KEY_D)
		data->obj_plyr->turn_direction = 1;
	else if (key == KEY_AROW_L || key == KEY_A)
		data->obj_plyr->turn_direction = -1;
	ft_update(data, key);
	ft_render_map(data);
	ft_render_player(data);
	return (0);
}

int main(int ac, char **av)
{
    t_data data;
	t_map	obj_map;
	t_player obj_plyr;
	t_img	obj_img;
    int     h;
    int     w;

    if (ac == 2)
    {
		// init player
		obj_plyr.radius = 3;
		obj_plyr.turn_direction = 0; // -1 if left , +1 if right
		obj_plyr.walk_direction = 0; // -1 if back , +1 if front
		obj_plyr.rotation_angle = 0;
		obj_plyr.move_speed = 0.15;
		obj_plyr.rotation_speed = 10 * (M_PI / 180);
		
		// init data
		data.obj_map = &obj_map;
		data.obj_img = &obj_img;
		data.obj_plyr = &obj_plyr;
		// data.tile_size = tilesize()
        data.mlx_ptr = mlx_init();
        ft_map_init(av[1], &data);
        h = data.obj_map->map_height * COLUMN_SIZE;
        w = data.obj_map->map_width * COLUMN_SIZE;
		printf("this h = %d and w = %d\n", h / COLUMN_SIZE, w / COLUMN_SIZE);
        data.win_ptr = mlx_new_window(data.mlx_ptr, w, h, "cube3D");
		
		ft_drawer_init(&data);
		ft_render_map(&data);
		ft_render_player(&data);
		mlx_hook(data.win_ptr, 02, 0, ft_key_handler, &data);
		mlx_hook(data.win_ptr, 17, 0, ft_exit_handler, &data);
		mlx_loop(data.mlx_ptr);
    }
    else
        printf("==> Please enter : ./cub3D [assets/maps/map_name.cub]\n");
}
