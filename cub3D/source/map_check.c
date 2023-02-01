
#include "cub3D.h"

// this function for get the player position 
// and check if there is more than one player.
static void	ft_update_plyr(t_data *data, int nbr_plyrs, int x, int y)
{
	t_map	*obj_map;

	obj_map = data->map;
	if (nbr_plyrs > 1)
		error_map(data, 2);
	obj_map->x_player = x;
	obj_map->y_player = y;
}

static int	ft_check_char(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'W'
		&& c != 'S' && c != 'E' && c != ' ')
		return (1);
	else if (c == 'W' || c == 'S'
		|| c == 'E' || c == 'N')
		return (2);
	return (0);
}

// this function check if there is more than one player 
// and if there is unwanted characters.
void	is_characters(t_data *data, t_map *obj_map)
{
	int		x;
	int		y;
	int		nbr_plyrs;
	char	**map;

	map = obj_map->map;
	y = -1;
	nbr_plyrs = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_check_char(map[y][x]) == 1)
				error_map(data, 1);
			else if (ft_check_char(map[y][x]) == 2)
			{
				nbr_plyrs++;
				ft_update_plyr(data, nbr_plyrs, x, y);
			}
		}
	}
	if (nbr_plyrs == 0)
		error_map(data, 2);
}

// this function check if the element surrounded by walls
void	ft_is_wall_exist(t_data *data, int y, int x)
{
	char	**map;
	t_map	*obj_map;

	obj_map = data->map;
	map = obj_map->map;
	if (y == 0 || y == obj_map->height - 1
		|| x == 0 || x == obj_map->width - 1
		|| map[y - 1][x] == ' ' || map[y + 1][x] == ' '
		|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		error_map(data, 3);
}

// this function check if the map surrounded by walls.
void	wall_checker(t_data *data, t_map *obj_map)
{
	int		x;
	int		y;
	char	**map;

	map = obj_map->map;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] != '1' && map[y][x] != ' ')
				ft_is_wall_exist(data, y, x);
		}
	}
}
