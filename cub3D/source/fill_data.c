
#include "cub3D.h"

static void	ft_fill_info(t_map *data, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		ft_maloc_error(split);
	if (!ft_strcmp(split[0], "NO"))
		data->no_texture_path = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "SO"))
		data->so_texture_path = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "WE"))
		data->we_texture_path = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "EA"))
		data->ea_texture_path = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "F"))
		data->f_color = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "C"))
		data->c_color = ft_strdup(split[1]);
	ft_free_split(split);
}

void	ft_fill_data(t_map *data, char *file)
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
			ft_fill_info(data, line);
		}
		free(line);
		if (len == 6)
			break ;
		line = get_next_line(fd);
	}
	close(fd);
}
