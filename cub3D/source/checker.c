
#include "cub3D.h"

/**
 * It checks if the file has the .cub extension
 * 
 * @param str the string to check
 * 
 * @return the length of the string.
 */
static int	check_extention(char *str)
{
	int		i;
	int		len;
	char	*cmp;

	i = 0;
	len = ft_strlen(str);
	cmp = ".cub";
	while (str && str[len - 4 + i] && i < 4)
	{
		if (str[len - 4 + i] != cmp[i])
			return (0);
		i++;
	}
	if (str && str[len - 4 + i])
		return (0);
	return (1);
}

/**
 * It checks if the parameter is valid, and if it is, it checks if the path is valid
 * 
 * @param str the parameter name
 * @param path the path to the file
 * 
 * @return the value of the variable i.
 */
static	int	is_valid_path(char *str, char *path)
{
	char	**word;
	int		i;
	int		number;

	i = 0;
	if(!str || !path)
		return (0);
	if (!is_param(str))
		return (0);
	if (!ft_strcmp(str, "F") || !ft_strcmp(str, "C"))
	{
		if (!valid_color(path))
			return (0);
		word = ft_split(path, ',');
		while (count_tab(word) == 3 && i != -1 && word[i])
		{
			number = ft_atoi(word[i]);
			if (number > 255 || number < 0)
				i = -2;
			i++;
		}
		free_loop(word);
		if (i == 0 || i == -1)
			return (0);
	}
	return (1);
}

/**
 * It checks if the line is a valid command line
 * 
 * @param line the line that is being read
 * @param flag a flag that is set to 1 if the line is valid, 0 otherwise.
 * @param len the number of lines in the file
 * @param number the number of parameters in the line
 */
void	valid_info(char *line, int *flag, int *len, int *number)
{
	char	**str;

	*flag = 0;
	str = ft_split(line, ' ');
	if (!str)
		ft_erorr(str);
	if (count_tab(str) == 2 || (count_tab(str) == 3
			&& str[count_tab(str) - 1][0] == '\n'))
		*flag = 1;
	*flag = *flag * is_valid_path(str[0], str[1]);
	*number = *number + param_number(str[0]);
	free_loop(str);
	(*len)++;
}

/**
 * It reads the first 6 lines of the file and checks if they are valid
 * 
 * @param fd file descriptor
 * 
 * @return 1 if the parsing is correct, 0 otherwise.
 */
int	read_param(int fd)
{
	int		flag;
	int		len;
	char	*line;
	int		number;

	flag = 1;
	len = 0;
	number = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n' && len < 6)
			valid_info(line, &flag, &len, &number);
		free(line);
		if (!flag)
			return (printf("Error\nError info\n"), 0);
		line = get_next_line(fd);
	}
	close(fd);
	if (len < 6 || number != 111111)
		return (printf("Error\nError parssing\n"), 0);
	return (1);
}

/**
 * It opens the file, checks if it's a .cub file, and then reads the parameters
 * 
 * @param file the file name
 * 
 * @return the value of the function read_param.
 */

int	map_checker(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nError file\n"), 0);
	if (!check_extention(file))
		return (printf("Error\nfile must be .cub\n"), 0);
	if (!read_param(fd))
		return (0);
	return (1);
}
