
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
		data.obj_map = &obj_map;
		data.obj_img = &obj_img;
		data.obj_plyr = &obj_plyr;
        data.mlx_ptr = mlx_init();
        ft_map_init(av[1], &data);
        h = data.obj_map->map_height * 50;
        w = data.obj_map->map_width * 50;
		printf("this h = %d and w = %d\n", h / 50, w / 50);
        data.win_ptr = mlx_new_window(data.mlx_ptr, w, h, "Free Fire");
		ft_drawer_init(&data);
		ft_draw(&data);
		// mlx_hook(data.win_ptr, 02, 0, ft_key_handler, &data.obj_game);
		mlx_hook(data.win_ptr, 17, 0, ft_exit_handler, &data);
		mlx_loop(data.mlx_ptr);
    }
    else
        printf("==> Please enter : ./cub3D [assets/maps/map_name.cub]\n");
}
