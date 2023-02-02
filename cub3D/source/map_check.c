
#include "cub3D.h"

/**
 * It updates the player's position on the map
 * 
 * @param var the structure that contains all the variables
 * @param player_num The player number, either 1 or 2.
 * @param x the x coordinate of the player
 * @param y the y coordinate of the player
 */
static void	update_player(t_var *var, int player_num, int x, int y)
{
	t_map	*map;

	map = var->map;
	if (player_num > 1)
		error_map(var, 2);
	map->x_player = x;
	map->y_player = y;
}

/**
 * It checks if the character is valid
 * 
 * @param c the character to check
 * 
 * @return the value of the character.
 */
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

/**
 * It checks if the map is valid
 * 
 * @param var a pointer to the t_var struct
 * @param tab the map
 */
void	is_characters(t_var *var, t_map *tab)
{
	char	**map;
	int		player_num;
	int		y;
	int		x;

	map = tab->map;
	y = -1;
	player_num = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_check_char(map[y][x]) == 1)
				error_map(var, 1);
			else if (ft_check_char(map[y][x]) == 2)
			{
				player_num++;
				update_player(var, player_num, x, y);
			}
		}
	}
	if (player_num == 0)
		error_map(var, 2);
}


/**
 * It checks if the map is surrounded by walls
 * 
 * @param var the structure that contains all the variables
 * @param y the y coordinate of the current position
 * @param x the x coordinate of the current position
 */
void	ft_is_wall_exist(t_var *var, int y, int x)
{
	char	**map;
	t_map	*full_map;

	full_map = var->map;
	map = full_map->map;
	if (y == 0 || y == full_map->height - 1
		|| x == 0 || x == full_map->width - 1
		|| map[y - 1][x] == ' ' || map[y + 1][x] == ' '
		|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		error_map(var, 3);
}


/**
 * It checks if the map is valid
 * 
 * @param var the structure that contains all the variables
 * @param full_map the map that was read from the file
 */
void	wall_checker(t_var *var, t_map *full_map)
{
	int		x;
	int		y;
	char	**map;

	map = full_map->map;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] != '1' && map[y][x] != ' ')
				ft_is_wall_exist(var, y, x);
		}
	}
}
