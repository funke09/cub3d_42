#include "cub3d.h"


int allocate_map(char **str, t_map *map)
{
    int i;
    char **map_str;

    i = 0;
    map_str = malloc(sizeof(char *) * (map->num_str + 2));
    if(!map_str)
    {
        free_loop(map->tmp);
        return (0);
    }
    while(is_map(str[i]))
    {
        map_str[i] = ft_strdup(str[i]);
        if(!map_str[i])
        {
            free_loop(map_str);
            free_loop(map->tmp);
            return (0);
        }
        i++;
    }
    map_str[i] = NULL;
    map->map = map_str;
    return (1);
}

int check_map(char **str, t_map *map)
{
    int i;

    i = 0;
    while(is_map(str[i]))
    {
        map->num_str = i;
        if(i == 0 && !check_first(str[i]))
            return(0);
        else if(!is_map(str[i + 1]))
        {
            if(i < 2)
                return(0);
            if(!check_player(map))
                return(0);
        }
        else
        {
            if(!map_is_protected(&str[i]))
                return(0);
            if(!if_no_or_multipule_player(map, str[i]))
                return(0);
        }
        i++;
    }
    if(!allocate_map(str, map))
        return (0);
    return (1);
}

int parssing_map(char **str, t_map *map)
{
    int i;
    int count;

    i = 0;
    count = 0;
    if(!check_parametrs(str, map, &count, &i))
        return (0);
    if(!str[i])
        printerror("Error: missing parameters\n");
    while(!is_map(str[i]) && str[i])
        i++;
    if(!str[i])
        printerror("Error: missing map\n");
    if(!check_map(&str[i], map))
        printerror("Error: invalid map\n");
    while(str[i] && is_map(str[i + 1]))
        i++;
    free_loop(map->tmp);
    return (1);
}


int sumilation(char *file_name)
{
    int fd;
    t_map *map;

    map = malloc(sizeof(t_map));
    init_map(map);
    fd = open(file_name, O_RDONLY);
    if(fd <= 0)
        printerror("Error: such file does not exist\n");
    if (!map->tmp)
        printerror("Error: map tmp failed\n");
    read_map(fd, map);
    if(!parssing_map(map->tmp, map))
        printerror("Error: parsing failed (Invalid map)");
    return (0);
    
}

int main(int ac, char **av)
{
    if(ac == 2)
    {
        if(is_the_file(av[1]))
            printerror("Error: invalid file");
        sumilation(av[1]);
    }
    else
       printerror("Error: usage ./cub3d map.cub");
}