
#include "cub3D.h"

// this function init the player attributes
void	init_player(t_player *player, t_var *var)
{
	int	w;

	w = var->map->width;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotate_angle = check_angle(var->player->player_derection);
	player->move_speed = 5;
	player->rotation_speed = 5 * (M_PI / 180);
	player->fov_angle = 60 * (M_PI / 180);
	player->wall_strip_width = 0.1;
	player->rays_num = (var->real_width / TILE_SIZE) \
		/ player->wall_strip_width;
	player->minimap_scale_factor = 0.2;
	var->map[(int)player->x][(int)player->y] = '0';
	// player->minimap_size = 0;
	if (var->map->width > var->map->height)
		player->minimap_size = var->real_width * player->minimap_scale_factor;
	else
		player->minimap_size = var->real_height * player->minimap_scale_factor;
	player->sizeofplayer = 30;
}

// this function init the the window and the texture
void	 ft_var_init(t_var *var)
{
	var->mlx_ptr = mlx_init();
	var->win_ptr = \
		mlx_new_window(var->mlx_ptr, var->real_width, var->real_height, "NAZISM");
	var->img = mlx_new_image(var->mlx_ptr, var->real_width, var->real_height);
	var->img_var = mlx_get_var_addr(var->img, &var->bits_per_pixel, \
	&var->line_length, &var->endian);
	init_texturs(var);
	render(var, RANDOM_KEY);
	mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, var->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_var		var;
	t_map		map;
	t_img		image;
	t_player	player;

	if (ac == 2)
	{
		var.map = &map;
		var.image = &image;
		var.player = &player;
		var.real_height = 1000;
		var.real_width = 2000;
		init_map(av[1], &var);
		init_player(&player, &var);
		ft_var_init(&var);
		mlx_hook(var.win_ptr, 02, 0, key_press, &var);
		mlx_hook(var.win_ptr, 17, 0, ft_destroy_window, &var);
		mlx_loop(var.mlx_ptr);
	}
	else
		printf("=> USAGE : ./cub3D [mapName.cub]\n");
}
