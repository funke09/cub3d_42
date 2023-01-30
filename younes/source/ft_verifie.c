
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
	if (!ft_is_flag(str))
		return (0);
	if (!ft_strcmp(str, "F") || !ft_strcmp(str, "C"))
	{
		if (!ft_is_gbr_valid(info))
			return (0);
		split = ft_split(info, ',');
		while (ft_len_split(split) == 3 && i != -1 && split[i])
		{
			nbr = ft_atoi(split[i]);
			if (nbr > 255 || nbr < 0)
				i = -2;
			i++;
		}
		ft_free_split(split);
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
		ft_maloc_error(split);
	if (ft_len_split(split) == 2 || (ft_len_split(split) == 3
			&& split[ft_len_split(split) - 1][0] == '\n'))
		*re = 1;
	*re = *re * identifier(split[0], split[1]);
	*nbr = *nbr + ft_nbr_flag(split[0]);
	ft_free_split(split);
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

int	ft_verifie(char *file)
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
