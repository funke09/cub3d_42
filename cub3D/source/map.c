
#include "cub3D.h"

/**
 * It reads the file until it finds a line that is not a newline character, and then returns that line
 * 
 * @param fd file descriptor
 * 
 * @return The length of the map.
 */
char	*len_map(int fd)
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

/**
 * It checks the line and sets the width of the map
 * 
 * @param var a pointer to the structure that holds all the variables
 * @param line the line read from the file
 * @param i the number of lines in the map
 * @param flag This is a flag that is used to check if the map is valid.
 */
static void	ft_check_line(t_var *var, char *line, int *i, int *flag)
{
	int	len;

	len = ft_strlen(line) - 1;
	if (var->map->width < len)
		var->map->width = len;
	if (line[0] != '\n' && *flag == 0)
		(*i)++;
	else if (line[0] == '\n' && *flag == 0)
		*flag = 1;
	else if (line[0] != '\n' && *flag == 1)
	{
		free(line);
		error_map(var, 4);
	}
}

/**
 * It opens the file, reads the first line, and then reads the rest of the file
 * 
 * @param path the path to the map file
 * @param var the structure that contains all the variables
 */

void	get_info_map(char *path, t_var *var)
{
	int		i;
	int		fd;
	int		flag;
	char	*line;

	i = 0;
	flag = 0;
	var->map->width = 0;
	fd = open(path, O_RDONLY);
	line = len_map(fd);
	while (line)
	{
		ft_check_line(var, line, &i, &flag);
		free(line);
		line = get_next_line(fd);
	}
	var->map->height = i;
	close(fd);
}

/**
 * It takes a string and a length, and returns a string of the same length, with the first non-null
 * character of the original string, and all subsequent characters replaced with spaces
 * 
 * @param s1 the string to be copied
 * @param len the length of the string to be duplicated
 * 
 * @return A pointer to a string.
 */
char	*dup_cub(char *s1, int len)
{
	int		i;
	char	*dst;
	int		flag;

	i = 0;
	flag = 0;
	dst = malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	while (i < len)
	{
		if (flag == 0 && s1[i] != '\0' && s1[i] != '\n')
			dst[i] = s1[i];
		else
			flag = 1;
		if (flag == 1)
			dst[i] = ' ';
		i++;
	}
	dst[i] = '\0';
	return (dst);
}


/**
 * It reads the map from the file and stores it in a 2D array
 * 
 * @param path the path to the map file
 * @param map_file a pointer to a t_map structure.
 */
void	to_array(char *path, t_map *map_file)
{
	int		i;
	int		fd;
	char	*line;
	int		len;
	char	**map;

	len = map_file->height + 1;
	map = (char **)malloc(sizeof(char *) * len);
	if (!map)
		ft_erorr(map);
	fd = open(path, O_RDONLY);
	i = -1;
	line = len_map(fd);
	while (line && ++i < (len - 1))
	{
		map[i] = dup_cub(line, map_file->width);
		free(line);
		line = get_next_line(fd);
	}
	map[len - 1] = NULL;
	map_file->map = map;
	close(fd);
}

/**
 * It reads the map file and stores the information in a struct
 * 
 * @param map_path the path to the map file
 * @param var a pointer to the global variable struct
 */

void	init_map(char *map_path, t_var *var)
{
	t_map	*global;

	if (!map_checker(map_path))
		exit(0);
	global = var->map;
	get_info_map(map_path, var);
	to_array(map_path, global);
	is_characters(var, global);
	wall_checker(var, global);
	get_info(global, map_path);
	var->player->player_derection = \
	global->map[global->y_player][global->x_player];
	var->player->x = global->x_player * TILE_SIZE + 2;
	var->player->y = global->y_player * TILE_SIZE + 2;
	global->floor_color_dc = convert_rgb_dec(0, check_color(global->floor_color, 1), \
	check_color(global->floor_color, 2), check_color(global->floor_color, 3));
	global->ceil_color_dc = convert_rgb_dec(0, check_color(global->ceil_color, 1), \
	check_color(global->ceil_color, 2), check_color(global->ceil_color, 3));
}
