
#include "cub3D.h"

/**
 *  this function goes to the 7 full line, in the normal it's
 *  the line that contain the map.
**/
char	*ft_go_to_map_line(int fd)
{
	char	*line;
	int		len;

	len = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
			len++;
		if (line[0] != '\n' && len > 6)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static void	ft_check_line(t_var *var, char *line, int *i, int *map_end)
{
	int	line_lenght;

	line_lenght = ft_strlen(line) - 1;
	if (var->map->width < line_lenght)
		var->map->width = line_lenght;
	if (line[0] != '\n' && *map_end == 0)
		(*i)++;
	else if (line[0] == '\n' && *map_end == 0)
		*map_end = 1;
	else if (line[0] != '\n' && *map_end == 1)
	{
		free(line);
		error_map(var, 4);
	}
}

// this function for get the width and the hight of the map
void	ft_map_dimensions(char *map_path, t_var *var)
{
	int		fd;
	int		i;
	char	*line;
	int		map_end;

	i = 0;
	map_end = 0;
	var->map->width = 0;
	fd = open(map_path, O_RDONLY);
	line = ft_go_to_map_line(fd);
	while (line)
	{
		ft_check_line(var, line, &i, &map_end);
		free(line);
		line = get_next_line(fd);
	}
	var->map->height = i;
	close(fd);
}
/**
 * It takes a string and a row length, and returns a string that is the same as the first string, but
 * with spaces added to the end of it until it reaches the row length
 * 
 * @param s1 the string to be copied
 * @param row_len the length of the row in the map
 * 
 * @return A pointer to a string.
 */
char	*ft_strdup_cub3D(char *s1, int row_len)
{
	int		i;
	char	*pdst;
	int		end;

	i = 0;
	end = 0;
	pdst = malloc(sizeof(char) * (row_len + 1));
	if (pdst == NULL)
		return (NULL);
	while (i < row_len)
	{
		if (end == 0 && s1[i] != '\0' && s1[i] != '\n')
			pdst[i] = s1[i];
		else
			end = 1;
		if (end == 1)
			pdst[i] = ' ';
		i++;
	}
	pdst[i] = '\0';
	return (pdst);
}

// this function for convert the map file to 2D char array
void	ft_fill_map(char *map_path, t_map *obj_map)
{
	int		i;
	int		fd;
	int		map_len;
	char	**map;
	char	*line;

	map_len = obj_map->height + 1;
	map = (char **)malloc(sizeof(char *) * map_len);
	if (!map)
		ft_erorr(map);
	fd = open(map_path, O_RDONLY);
	i = -1;
	line = ft_go_to_map_line(fd);
	while (line && ++i < (map_len - 1))
	{
		map[i] = ft_strdup_cub3D(line, obj_map->width);
		free(line);
		line = get_next_line(fd);
	}
	map[map_len - 1] = NULL;
	obj_map->map = map;
	close(fd);
}

// this function init the map
void	init_map(char *map_path, t_var *var)
{
	t_map	*obj_map;

	if (!map_checker(map_path))
		exit(0);
	obj_map = var->map;
	ft_map_dimensions(map_path, var);
	ft_fill_map(map_path, obj_map);
	is_characters(var, obj_map);
	wall_checker(var, obj_map);
	get_info(obj_map, map_path);
	var->player->player_derection = \
	obj_map->map[obj_map->y_player][obj_map->x_player];
	var->player->x = obj_map->x_player * TILE_SIZE + 2;
	var->player->y = obj_map->y_player * TILE_SIZE + 2;
	obj_map->floor_color_dc = convert_rgb_dec(0, check_color(obj_map->floor_color, 1), \
	check_color(obj_map->floor_color, 2), check_color(obj_map->floor_color, 3));
	obj_map->ceil_color_dc = convert_rgb_dec(0, check_color(obj_map->ceil_color, 1), \
	check_color(obj_map->ceil_color, 2), check_color(obj_map->ceil_color, 3));
}
