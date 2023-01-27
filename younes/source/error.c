

#include "cub3D.h"

void ft_maloc_error(void *var)
{
    free(var);
    exit(1);
}

void	ft_map_errors(t_map *obj_map, int error_num)
{
	int	i;

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
		exit(0);
	}
	i = -1;
	while (obj_map->map[++i] != NULL)
		free(obj_map->map[i]);
	free(obj_map->map);
	exit(0);
}