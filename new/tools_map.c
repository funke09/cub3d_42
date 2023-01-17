#include "cub3d.h"


int is_sprite(char *str, t_map *map)
{
    int i;

    i = 1;
    if(map->sprite)
        return (0);
    while(str[i] == ' ')
        i++;
    map->sprite = ft_strdup(str + i);
    if(!map->sprite)
        return (0);
    if(open(map->sprite, O_RDONLY) == -1)
        return (0);
    return (1);
}

int is_floorcolor(char *str, t_map *map)
{
    int i;

    i = 1;
    if(map->r_floor || map->g_floor || map->b_floor)
        return (0);
    while(is_blank(str[i]) || str[i] == ',')
        i++;
    if(!ft_isdigit(str[i]))
        return (0);
    map->r_floor = ft_atoi(str + i);
    while(ft_isdigit(str[i]))
        i++;
    while(is_blank(str[i])|| str[i] == ',')
        i++;
    if(!ft_isdigit(str[i]))
        return (0);
    map->g_floor = ft_atoi(str + i);
    while(ft_isdigit(str[i]))
        i++;
    while(is_blank(str[i]) || str[i] == ',')
        i++;
    if(!ft_isdigit(str[i]))
        return (0);
    map->b_floor = ft_atoi(str + i);
    if(map->r_floor < 0 || map->r_floor > 255 || map->g_floor < 0 || map->g_floor > 255 || map->b_floor < 0 || map->b_floor > 255)
        return (0);
    return (1);

}

int is_char(char **str, int *i)
{
    if(str[(*i)][0] == 'N' && str[(*i)][1] == 'O')
        return (1);
    if(str[(*i)][0] == 'S' && str[(*i)][1] == 'O')
        return (1);
    if(str[(*i)][0] == 'W' && str[(*i)][1] == 'E')
        return (1);
    if(str[(*i)][0] == 'E' && str[(*i)][1] == 'A')
        return (1);
    if(str[(*i)][0] == 'S' && str[(*i)][1] == ' ')
        return (1);
    if(str[(*i)][0] == 'F' && str[(*i)][1] == ' ')
        return (1);
    if(str[(*i)][0] == 'C' && str[(*i)][1] == ' ')
        return (1);
    if(str[(*i)][0] == '\0')
        return (1);
    if (str[(*i)] == NULL)
        return (1);
    return (0);
}

int is_ceilingcolor(char *str, t_map *map)
{
    int i;

    i = 1;
    if(map->r_ceiling || map->g_ceiling || map->b_ceiling)
        return (0);
    while(is_blank(str[i]) || str[i] == ',')
        i++;
    if(!ft_isdigit(str[i]))
        return (0);
    map->r_ceiling = ft_atoi(str + i);
    while(ft_isdigit(str[i]))
        i++;
    while(is_blank(str[i]) || str[i] == ',')
        i++;
    if(!ft_isdigit(str[i]))
        return (0);
    map->g_ceiling = ft_atoi(str + i);
    while(ft_isdigit(str[i]))
        i++;
    while(is_blank(str[i]) || str[i] == ',')
        i++;
    if(!ft_isdigit(str[i]))
        return (0);
    map->b_ceiling = ft_atoi(str + i);
    if(map->r_ceiling < 0 || map->r_ceiling > 255 || map->g_ceiling < 0 || map->g_ceiling > 255 || map->b_ceiling < 0 || map->b_ceiling > 255)
        return (0);
    return (1);
}


int is_map(char *str)
{
    int i;

    i = 0;
    if(!str || !*str)
        return (0);
    while(str[i])
    {
        if(!is_blank(str[i]) && str[i] != '1' && str[i] != '0' && str[i] != '2' && str[i] != 'N' && str[i] != 'S' && str[i] != 'W' && str[i] != 'E')
            return (0);
        i++;
    }
    return (1);
}