
#include "cub3D.h"

int ft_is_gbr_valid(char *str)
{
    int i;

    i = 0;
    while (str && str[i] && str[i] != '\n')
    {
        if ((str[i] >= '0' && str[i] <= '9') || str[i] == ',')
        {
            if (str[i] == ',' && str[i + 1] == ',')
                return (0);
            i++;
        }
        else
            return (0);
    }
    return (1);
}

static int ft_extension(char *str)
{
    int i;
    int len;
    char *exte;

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

static int identifier(char *str, char *info)
{
    char **split;
    int i;
    int nbr;

    i = 0;
    if (!ft_strcmp(str, "NO") || !ft_strcmp(str, "SO") ||
        !ft_strcmp(str, "WE") || !ft_strcmp(str, "EA") ||
        !ft_strcmp(str, "F") || !ft_strcmp(str, "C"))
        ;
    else
        return (0);
    if (!ft_strcmp(str, "F") || !ft_strcmp(str, "C"))
    {
        if (!ft_is_gbr_valid(info))
            return (0);
        split = ft_split(info, ',');
        while (ft_len_split(split) == 3 && i != -1 && split[i])
        {
            nbr  = ft_atoi(split[i]);
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

static int ft_information(char *file)
{
    int fd;
    char *line;
    char **split;
    int re;
    int len;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (printf("Error\nError fd\n"), 0);
    re = 1;
    len = 0;
    while ((line = get_next_line(fd)))
    {
        if (line[0] != '\n' && len < 6)
        {
            re = 0;
            split = ft_split(line, ' ');
            if (ft_len_split(split) == 2 || (ft_len_split(split) == 3 && split[ft_len_split(split) - 1][0] == '\n'))
                re = 1;
            re = re * identifier(split[0], split[1]);
            ft_free_split(split);
            len++;
        }
        free(line);
        if (!re)
            return (printf("Error\nError info\n"), 0);
    }
    close(fd);
    if (len < 6)
        return (printf("Error\nError info\n"), 0);
    return (1);
}

int ft_verifie(char *file)
{
    if (!ft_extension(file))
        return (printf("Error\nExtension must be .cub\n"), 0);
    if (!ft_information(file))
        return (0);
    return (1);
}