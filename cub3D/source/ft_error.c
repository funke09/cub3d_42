
#include "cub3D.h"

void	ft_erorr(void *var)
{
	if (var)
		free(var);
	exit(1);
}

void	destroy_textures(t_data *data)
{
	if (data->image->ea_texture)
		free(data->image->ea_texture);
	if (data->image->we_texture)
		free(data->image->we_texture);
	if (data->image->no_texture)
		free(data->image->no_texture);
	if (data->image->so_texture)
		free(data->image->so_texture);
}

// this function handles the maps errors and free the map
void	error_map(t_data *data, int error_num)
{
	int		i;
	t_map	*map;

	map = data->map;
	printf("Error\n==> ");
	if (error_num == 1)
		printf("a map must contain only the 6 chars: [0, 1, W, N, E, S]\n");
	else if (error_num == 2)
		printf("a map must contain one Player.\n");
	else if (error_num == 3)
		printf("a map must be surrounded by walls [1].\n");
	else if (error_num == 4)
	{
		printf("a map can't be separated by new line.\n");
		exit(1);
	}
	else if (error_num == 5)
		printf("invalid textures.\n");
	i = -1;
	while (map->map[++i])
		free(map->map[i]);
	free(map->map);
	exit(1);
}
