
#include "cub3D.h"

// this function init the obj_plyr attributes
void	ft_plyr_init(t_player *obj_plyr, t_data *data)
{
	int	w;

	w = data->obj_map->map_width;
	obj_plyr->turn_direction = 0;
	obj_plyr->walk_direction = 0;
	obj_plyr->rotate_angle = ft_get_rot_angle(data->obj_plyr->p_orientation);
	obj_plyr->move_speed = 5;
	obj_plyr->rotation_speed = 3 * (M_PI / 180);
	obj_plyr->fov_angle = 60 * (M_PI / 180);
	obj_plyr->wall_strip_width = 0.1;
	obj_plyr->rays_num = (data->fix_w / COLUMN_SIZE) \
		/ obj_plyr->wall_strip_width;
	obj_plyr->minimap_scale_factor = 0.2;
	// obj_plyr->minimap_size = 0;
	if (data->obj_map->map_width > data->obj_map->map_height)
		obj_plyr->minimap_size = data->fix_w * obj_plyr->minimap_scale_factor;
	else
		obj_plyr->minimap_size = data->fix_h * obj_plyr->minimap_scale_factor;
	obj_plyr->player_size = 30;
}

// this function init the the window and the texture
void	ft_data_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = \
		mlx_new_window(data->mlx_ptr, data->fix_w, data->fix_h, "cub3D");
	data->img = mlx_new_image(data->mlx_ptr, data->fix_w, data->fix_h);
	data->img_data = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
	&data->line_length, &data->endian);
	ft_textures_init(data);
	ft_render(data, KEY_RANDOM);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_map		obj_map;
	t_img		obj_img;
	t_player	obj_plyr;

	if (ac == 2)
	{
		data.obj_map = &obj_map;
		data.obj_img = &obj_img;
		data.obj_plyr = &obj_plyr;
		data.fix_h = 1000;
		data.fix_w = 2000;
		ft_map_init(av[1], &data);
		ft_plyr_init(&obj_plyr, &data);
		ft_data_init(&data);
		mlx_hook(data.win_ptr, 02, 0, ft_key_handler, &data);
		mlx_hook(data.win_ptr, 17, 0, ft_exit_handler, &data);
		mlx_loop(data.mlx_ptr);
	}
	else
		printf("==> Please enter : ./cub3D [assets/maps/map_name.cub]\n");
}
