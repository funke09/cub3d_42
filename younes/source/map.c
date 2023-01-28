#include "cub3D.h"

char    *ft_go_to_map_line(int fd)
{
    char    *line;
    int     len;
    
    len = 0;
    line = get_next_line(fd);
    while (line)
    {
        if (line[0] != '\n')
            len++;
        if (line[0] != '\n' && len > 6)
            break;
        free(line);
        line = get_next_line(fd);
    }
    return (line);
}

// this function for get the width and the hight of the map
void ft_map_dimensions(char *map_path, t_data *data)
{
    int fd;
    int i;
    char *line;
    int line_lenght;
    int map_end;

    i = 0;
    data->obj_map->map_width = 0;
    line_lenght = 0;
    fd = open(map_path, O_RDONLY);
    map_end = 0;
    line = ft_go_to_map_line(fd);
    while (line)
    {
        line_lenght = ft_strlen(line) - 1;
        if (data->obj_map->map_width < line_lenght)
            data->obj_map->map_width = line_lenght;
        if (line[0] != '\n' && map_end == 0)
            i++;
        else if (line[0] == '\n' && map_end == 0)
            map_end = 1;
        else if (line[0] != '\n' && map_end == 1)
            free(line),ft_map_errors(data->obj_map, 4);
        free(line);
        line = get_next_line(fd);
    }
    data->obj_map->map_height = i;
    close(fd);
}

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
void ft_fill_map(char *map_path, t_map *obj_map)
{
    int i;
    int fd;
    int map_len;
    char **map;
    char *line;

    map_len = obj_map->map_height + 1;
    map = (char **)malloc(sizeof(char *) * map_len);
    if (!map)
        ft_maloc_error(map);
    fd = open(map_path, O_RDONLY);
    i = -1;
    line = ft_go_to_map_line(fd);
    while (line && ++i < (map_len - 1))
    {
        map[i] = ft_strdup_cub3D(line, obj_map->map_width);
        if (!map[i])
            ft_maloc_error(map[i]);
        free(line);
        line = get_next_line(fd);
    }
    map[map_len - 1] = NULL;
    obj_map->map = map;
    close(fd);
}

void ft_print_map(char **map)
{
    int i;

    i = -1;
    while (map[++i])
    {
        printf("|%s|\n", map[i]);
    }
}

void ft_map_init(char *map_path, t_data *data)
{    
    if (!ft_verifie(map_path))
        exit(0);
    ft_map_dimensions(map_path, data);
    ft_fill_map(map_path, data->obj_map);
    ft_check_characters(data->obj_map);
    ft_check_walls(data->obj_map);
    ft_print_map(data->obj_map->map);
    ft_fill_data(data->obj_map, map_path);
    data->obj_plyr->x = data->obj_map->plyr_x * COLUMN_SIZE;
    data->obj_plyr->y = data->obj_map->plyr_y * COLUMN_SIZE;
}
