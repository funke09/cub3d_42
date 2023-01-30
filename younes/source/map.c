
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

static void	ft_check_line(t_data *data, char *line, int *i, int *map_end)
{
	int	line_lenght;

	line_lenght = ft_strlen(line) - 1;
	if (data->obj_map->map_width < line_lenght)
		data->obj_map->map_width = line_lenght;
	if (line[0] != '\n' && *map_end == 0)
		(*i)++;
	else if (line[0] == '\n' && *map_end == 0)
		*map_end = 1;
	else if (line[0] != '\n' && *map_end == 1)
	{
		free(line);
		ft_map_errors(data, 4);
	}
}

// this function for get the width and the hight of the map
void	ft_map_dimensions(char *map_path, t_data *data)
{
	int		fd;
	int		i;
	char	*line;
	int		map_end;

	i = 0;
	map_end = 0;
	data->obj_map->map_width = 0;
	fd = open(map_path, O_RDONLY);
	line = ft_go_to_map_line(fd);
	while (line)
	{
		ft_check_line(data, line, &i, &map_end);
		free(line);
		line = get_next_line(fd);
	}
	data->obj_map->map_height = i;
	close(fd);
}

// this function for convert the map file to 2D char array
void	ft_fill_map(char *map_path, t_map *obj_map)
{
	int		i;
	int		fd;
	int		map_len;
	char	**map;
	char	*line;

	map_len = obj_map->map_height + 1;
	map = (char **)malloc(sizeof(char *) * map_len);
	if (!map)
		ft_maloc_error(map);
	fd = open(map_path, O_RDONLY);
	i = -1;
	line = ft_go_to_map_line(fd);
	while (line && ++i < (map_len - 1))
	{
		map[i] = ft_strdup_cub3d(line, obj_map->map_width);
		free(line);
		line = get_next_line(fd);
	}
	map[map_len - 1] = NULL;
	obj_map->map = map;
	close(fd);
}

// this function init the map
void	ft_map_init(char *map_path, t_data *data)
{
	t_map	*obj_map;

	if (!ft_verifie(map_path))
		exit(0);
	obj_map = data->obj_map;
	ft_map_dimensions(map_path, data);
	ft_fill_map(map_path, obj_map);
	ft_check_characters(data, obj_map);
	ft_check_walls(data, obj_map);
	ft_fill_data(obj_map, map_path);
	data->obj_plyr->p_orientation = \
	obj_map->map[obj_map->plyr_y][obj_map->plyr_x];
	data->obj_plyr->x = obj_map->plyr_x * COLUMN_SIZE + 2;
	data->obj_plyr->y = obj_map->plyr_y * COLUMN_SIZE + 2;
	obj_map->f_color_d = ft_trgb_to_dec(0, ft_get_color(obj_map->f_color, 1), \
	ft_get_color(obj_map->f_color, 2), ft_get_color(obj_map->f_color, 3));
	obj_map->c_color_d = ft_trgb_to_dec(0, ft_get_color(obj_map->c_color, 1), \
	ft_get_color(obj_map->c_color, 2), ft_get_color(obj_map->c_color, 3));
}
