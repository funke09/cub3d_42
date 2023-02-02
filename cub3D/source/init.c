
#include "cub3D.h"

/**
 * It takes a line from the map file and fills the appropriate variable in the t_map struct
 * 
 * @param var a pointer to the structure that holds all the information about the map.
 * @param line the line of the map file that is being read
 */
static void	ft_fill_info(t_map *var, char *line)
{
	char	**str;

	str = ft_split(line, ' ');
	if (!str)
		ft_erorr(str);
	if (!ft_strcmp(str[0], "NO"))
		var->no_texture = ft_strdup(str[1]);
	else if (!ft_strcmp(str[0], "SO"))
		var->so_texture = ft_strdup(str[1]);
	else if (!ft_strcmp(str[0], "WE"))
		var->we_texture = ft_strdup(str[1]);
	else if (!ft_strcmp(str[0], "EA"))
		var->ea_texture = ft_strdup(str[1]);
	else if (!ft_strcmp(str[0], "F"))
		var->floor_color = ft_strdup(str[1]);
	else if (!ft_strcmp(str[0], "C"))
		var->ceil_color = ft_strdup(str[1]);
	free_loop(str);
}

/**
 * It reads the first 6 lines of the file and stores the information in the struct
 * 
 * @param var a pointer to a t_map struct, which is defined in the header file.
 * @param file the file name
 */
void	get_info(t_map *var, char *file)
{
	int		fd;
	char	*line;
	int		len;

	fd = open(file, O_RDONLY);
	len = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n' && len < 6)
		{
			len++;
			line[ft_strlen(line) - 1] = 0;
			ft_fill_info(var, line);
		}
		free(line);
		if (len == 6)
			break ;
		line = get_next_line(fd);
	}
	close(fd);
}
