
#include "cub3D.h"

// this function handles the exit of the game when 
// clicking the red cross or the ESK
int	ft_exit_handler(void *n_data)
{
	t_data	*data;
	int		i;

	data = (t_data *)n_data;
	i = -1;
	while (data->map->map[++i] != NULL)
		free(data->map->map[i]);
	free(data->map->map);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}

// this funciton handles the click on the keys
int	ft_key_handler(int key, void *n_data)
{
	t_data	*data;

	data = (t_data *) n_data;
	if (key == KEY_ESC)
		ft_exit_handler(data);
	else if (key == KEY_W)
		data->player->walk_direction = 1;
	else if (key == KEY_S)
		data->player->walk_direction = -1;
	else if (key == KEY_RIGHT || key == KEY_D)
		data->player->turn_direction = 1;
	else if (key == KEY_LEFT || key == KEY_A)
		data->player->turn_direction = -1;
	ft_render(data, key);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return (0);
}
