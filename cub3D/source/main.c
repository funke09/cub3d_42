
#include "cub3D.h"

// this function init the player attributes
void	ft_plyr_init(t_player *player, t_data *data)
{
	int	w;

	w = data->map->width;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotate_angle = ft_get_rot_angle(data->player->player_derection);
	player->move_speed = 30;
	player->rotation_speed = 10 * (M_PI / 180);
	player->fov_angle = 60 * (M_PI / 180);
	player->wall_strip_width = 0.1;
	player->rays_num = (data->real_width / TILE_SIZE) \
		/ player->wall_strip_width;
	player->minimap_scale_factor = 0.2;
	// player->minimap_size = 0;
	if (data->map->width > data->map->height)
		player->minimap_size = data->real_width * player->minimap_scale_factor;
	else
		player->minimap_size = data->real_height * player->minimap_scale_factor;
	player->sizeofplayer = 30;
}

// this function init the the window and the texture
void	ft_data_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = \
		mlx_new_window(data->mlx_ptr, data->real_width, data->real_height, "NAZISM");
	data->img = mlx_new_image(data->mlx_ptr, data->real_width, data->real_height);
	data->img_data = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
	&data->line_length, &data->endian);
	ft_textures_init(data);
	ft_render(data, RANDOM_KEY);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_map		map;
	t_img		image;
	t_player	player;

	if (ac == 2)
	{
		data.map = &map;
		data.image = &image;
		data.player = &player;
		data.real_height = 1000;
		data.real_width = 2000;
		ft_map_init(av[1], &data);
		ft_plyr_init(&player, &data);
		ft_data_init(&data);
		mlx_hook(data.win_ptr, 02, 0, ft_key_handler, &data);
		mlx_hook(data.win_ptr, 17, 0, ft_exit_handler, &data);
		mlx_loop(data.mlx_ptr);
	}
	else
		printf("=> USAGE : ./cub3D [mapName.cub]\n");
}
