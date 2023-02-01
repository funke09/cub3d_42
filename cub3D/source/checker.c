
#include "cub3D.h"

static int	ft_extension(char *str)
{
	int		i;
	int		len;
	char	*exte;

	i = 0;
	len = ft_strlen(str);
	exte = ".cub";
	while (str && str[len - 4 + i] && i < 4)
	{
		if (str[len - 4 + i] != exte[i])
			return (0);
		i++;
	}
	if (str && str[len - 4 + i])
		return (0);
	return (1);
}

static	int	identifier(char *str, char *info)
{
	char	**split;
	int		i;
	int		nbr;

	i = 0;
	if(!str || !info)
		return (0);
	if (!is_param(str))
		return (0);
	if (!ft_strcmp(str, "F") || !ft_strcmp(str, "C"))
	{
		if (!valid_color(info))
			return (0);
		split = ft_split(info, ',');
		while (count_tab(split) == 3 && i != -1 && split[i])
		{
			nbr = ft_atoi(split[i]);
			if (nbr > 255 || nbr < 0)
				i = -2;
			i++;
		}
		free_loop(split);
		if (i == 0 || i == -1)
			return (0);
	}
	return (1);
}

void	ft_body_info(char *line, int *re, int *len, int *nbr)
{
	char	**split;

	*re = 0;
	split = ft_split(line, ' ');
	if (!split)
		ft_erorr(split);
	if (count_tab(split) == 2 || (count_tab(split) == 3
			&& split[count_tab(split) - 1][0] == '\n'))
		*re = 1;
	*re = *re * identifier(split[0], split[1]);
	*nbr = *nbr + param_number(split[0]);
	free_loop(split);
	(*len)++;
}

int	ft_information(int fd)
{
	char	*line;
	int		re;
	int		len;
	int		nbr;

	re = 1;
	len = 0;
	nbr = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n' && len < 6)
			ft_body_info(line, &re, &len, &nbr);
		free(line);
		if (!re)
			return (printf("Error\nError info\n"), 0);
		line = get_next_line(fd);
	}
	close(fd);
	if (len < 6 || nbr != 111111)
		return (printf("Error\nError info\n"), 0);
	return (1);
}

int	map_checker(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nError fd\n"), 0);
	if (!ft_extension(file))
		return (printf("Error\nExtension must be .cub\n"), 0);
	if (!ft_information(fd))
		return (0);
	return (1);
}
