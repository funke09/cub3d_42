
#include "cub3D.h"

// this function handles the exit of the game when 
// clicking the red cross or the ESK
int	ft_destroy_window(void *n_var)
{
	t_var	*var;
	int		i;

	var = (t_var *)n_var;
	i = -1;
	while (var->map->map[++i] != NULL)
		free(var->map->map[i]);
	free(var->map->map);
	mlx_destroy_window(var->mlx_ptr, var->win_ptr);
	exit(0);
}

// this funciton handles the click on the keys
int	key_press(int key, void *n_var)
{
	t_var	*var;

	var = (t_var *) n_var;
	if (key == KEY_ESC)
		ft_destroy_window(var);
	else if (key == KEY_W || key == KEY_D)
	{
		var->player->turn_direction = 0;
		var->player->walk_direction = 1;
	}
	else if (key == KEY_S || key == KEY_A)
	{
		var->player->turn_direction = 0;
		var->player->walk_direction = -1;
	}
	else if (key == KEY_RIGHT)
	{
		var->player->walk_direction = 0;
		var->player->turn_direction = 1;
	}
	else if (key == KEY_LEFT || key == KEY_A)
	{
		var->player->walk_direction = 0;
		var->player->turn_direction = -1;
	}
	render(var, key);
	mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, var->img, 0, 0);
	return (0);
}
