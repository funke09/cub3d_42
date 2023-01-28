#include "cub3D.h"

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
	ft_clear_window(data);
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
	ft_render(data, key);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
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
		// init data
		data.obj_map = &obj_map;
		data.obj_img = &obj_img;
		data.obj_plyr = &obj_plyr;
        data.mlx_ptr = mlx_init();
        ft_map_init(av[1], &data);
		
		// init player
		obj_plyr.radius = 3;
		obj_plyr.turn_direction = 0; // -1 if left , +1 if right
		obj_plyr.walk_direction = 0; // -1 if back , +1 if front
		obj_plyr.rotation_angle = M_PI / 2;
		obj_plyr.move_speed = 5;
		obj_plyr.rotation_speed = 4 * (M_PI / 180);
		obj_plyr.fov_angle = 60 * (M_PI / 180);
		obj_plyr.wall_strip_width = 0.1;
		obj_plyr.rays_num = (data.obj_map->map_width) / obj_plyr.wall_strip_width;
		obj_plyr.minimap_scale_factor = 0.2;
		
        h = data.obj_map->map_height * COLUMN_SIZE;
        w = data.obj_map->map_width * COLUMN_SIZE;
		printf("this h = %d and w = %d\n", h / COLUMN_SIZE, w / COLUMN_SIZE);
        data.win_ptr = mlx_new_window(data.mlx_ptr, w, h, "cube3D");
		data.img = mlx_new_image(data.mlx_ptr, 1920, 1080);
		data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
		
		ft_imgs_init(&data);
		ft_render(&data, 999999);
		mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 0, 0);
		mlx_hook(data.win_ptr, 02, 0, ft_key_handler, &data);
		mlx_hook(data.win_ptr, 17, 0, ft_exit_handler, &data);
		mlx_loop(data.mlx_ptr);
    }
    else
        printf("==> usage : ./cub3D [map_name.cub]\n");
}
