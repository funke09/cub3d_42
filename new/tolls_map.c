#include "cub3d.h"


int go_resolution(char *str, t_map *map)
{
    int i;

    i = 1;
    while(str[i] == ' ')
        i++;
    map->res_x = ft_atoi(str + i);
    while(ft_isdigit(str[i]))
        i++;
    while(str[i] == ' ')
        i++;
    map->res_y = ft_atoi(str + i);
    if(map->res_x <= 0 || map->res_y <= 0 || map->res_x > MAX_X || map->res_y > MAX_Y)
        return (0);
    return (1);
}

int go_north(char *str, t_map *map)
{
    int i;

    i = 2;
    if(map->no)
        return (0);
    while(str[i] == ' ')
        i++;
    map->no = ft_strdup(str + i);
    if(!map->no)
        return (0);
    if(open(map->no, O_RDONLY) == -1)
        return (0);
    return (1);
}

int go_south(char *str, t_map *map)
{
    int i;

    i = 2;
    if(map->so)
        return (0);
    while(str[i] == ' ')
        i++;
    map->so = ft_strdup(str + i);
    if(!map->so)
        return (0);
    if(open(map->so, O_RDONLY) == -1)
        return (0);
    return (1);
}

int go_west(char *str, t_map *map)
{
    int i;

    i = 2;
    if(map->we)
        return (0);
    while(str[i] == ' ')
        i++;
    map->we = ft_strdup(str + i);
    if(!map->we)
        return (0);
    if(open(map->we, O_RDONLY) == -1)
        return (0);
    return (1);
}

int go_east(char *str, t_map *map)
{
    int i;

    i = 2;
    if(map->ea)
        return (0);
    while(str[i] == ' ')
        i++;
    map->ea = ft_strdup(str + i);
    if(!map->ea)
        return (0);
    if(open(map->ea, O_RDONLY) == -1)
        return (0);
    return (1);
}