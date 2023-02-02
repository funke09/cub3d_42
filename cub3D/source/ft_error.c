
#include "cub3D.h"

/**
 * *|CURSOR_MARCADOR|*
 * 
 * @param ptr The pointer to the memory that needs to be freed.
 */
void	ft_erorr(void *ptr)
{
	if (ptr)
		free(ptr);
	exit(1);
}

/**
 * It frees the memory allocated for the textures
 * 
 * @param var the structure that contains all the information about the game.
 */
void	destroy_textures(t_var *var)
{
	if (var->image->ea_texture)
		free(var->image->ea_texture);
	if (var->image->we_texture)
		free(var->image->we_texture);
	if (var->image->no_texture)
		free(var->image->no_texture);
	if (var->image->so_texture)
		free(var->image->so_texture);
}

/**
 * It checks if the map is valid, if not, it prints an error message and exits the program
 * 
 * @param var is a pointer to the structure that contains all the variables of the game.
 * @param number the error number.
 */
void	error_map(t_var *var, int number)
{
	int		i;
	t_map	*map;

	map = var->map;
	printf("Error ==> ");
	if (number == 1)
		printf("map must contain only the 6 chars: [0, 1, W, N, E, S]\n");
	else if (number == 2)
		printf("map must contain just one Player.\n");
	else if (number == 3)
		printf("map must be surrounded by walls [1].\n");
	else if (number == 4)
	{
		printf("map separated by new line.\n");
		exit(1);
	}
	else if (number == 5)
		printf("invalid path of texture.\n");
	i = -1;
	while (map->map[++i])
		free(map->map[i]);
	free(map->map);
	exit(1);
}
