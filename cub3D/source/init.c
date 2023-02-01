
#include "cub3D.h"

static void	ft_fill_info(t_map *var, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		ft_erorr(split);
	if (!ft_strcmp(split[0], "NO"))
		var->no_texture = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "SO"))
		var->so_texture = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "WE"))
		var->we_texture = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "EA"))
		var->ea_texture = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "F"))
		var->floor_color = ft_strdup(split[1]);
	else if (!ft_strcmp(split[0], "C"))
		var->ceil_color = ft_strdup(split[1]);
	free_loop(split);
}

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
