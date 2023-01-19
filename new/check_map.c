#include "cub3d.h"


int check_parametrs(char **str, t_map *map, int *count, int *i)
{
    while(str[*i] && (*count) < 8)
    {
        if(str[*i][0] == 'R' && str[*i][1] == ' ')
        {
            if(!go_resolution(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'N' && str[*i][1] == 'O' && str[*i][2] == ' ')
        {
            if(!go_north(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'S' && str[*i][1] == 'O' && str[*i][2] == ' ')
        {
            if(!go_south(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'W' && str[*i][1] == 'E' && str[*i][2] == ' ')
        {
            if(!go_west(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'E' && str[*i][1] == 'A' && str[*i][2] == ' ')
        {
            if(!go_east(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'S' && str[*i][1] == ' ')
        {
            if(!is_sprite(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'F' && str[*i][1] == ' ')
        {
            if(!is_floorcolor(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'C' && str[*i][1] == ' ')
        {
            if(!is_ceilingcolor(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(!is_char(str, i))
            return (0);
        else if(str[*i][0] == '\0')
            (*i)++;
    }
    return (1);
}


int check_first(char *str)
{
    int i;

    i = 0;
   while(str[i])
    {
        if(!is_blank(str[i]) && str[i] != '1')
        {
            return (0);
        }
        i++;
    }
    return (1);
}

int check_player(t_map *map)
{
    if(map->player == 0)
        return (0);
    return (1);
}

int if_no_or_multipule_player(t_map *map, char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
        {
            if(map->player == 0)
                map->player = str[i];
            else
                return (0);
        }
        i++;
    }
    return (1);
}

int map_is_protected(char **str)
{
    size_t i;

    i = 0;
    while(str[0][i])
    {
        if (i + 1 > ft_strlen(str[0]))
            return (0);
        if(str[0][i] == '0' || str[0][i] == '2' || str[0][i] == 'N' || str[0][i] == 'S' || str[0][i] == 'W' || str[0][i] == 'E')
        {
            if(!str[-1][i] || !str[1][i] || !str[0][i - 1] || !str[0][i + 1])
                return (0);
            if(is_blank(str[-1][i]) || is_blank(str[1][i]) || is_blank(str[0][i - 1]) || is_blank(str[0][i + 1]))
                return (0);
        }
        i++;
    }
    return (1);
}