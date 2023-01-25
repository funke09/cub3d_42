#include "cub3d.h"

void printerror(char *message)
{
    printf("%s\n", message);
    exit(1);
}

int is_blank(char c)
{
    if(c == ' ' || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

void *free_loop(char **str)
{
    int i;

    i = 0;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
    return (0);
}
// function int is_the_file(char *file) that check if the file is a .cub file
int is_the_file(char *file)
{
    int i;

    i = 0;
    while(file[i])
    {
        if(file[i] == '.')
        {
            if(file[i + 1] == 'c' && file[i + 2] == 'u' && file[i + 3] == 'b' && !file[i + 4])
                return (0);
            return (1);
        }
        i++;
    }
    return (1);
}

// map.cub
void init_map(t_map *map)
{
    if(!map)
        printerror("Error: malloc failed");
    map->tmp = malloc(sizeof(char *) * 2);
    if(!map->tmp || !map->tmp[0] || !map->tmp[1])
        printerror("Error: malloc failed");
    map->tmp[0] = 0;
    map->tmp[1] = 0;
    map->map = NULL;
    map->no = NULL;
    map->so= NULL;
    map->we = NULL;
    map->ea = NULL;
    map->sprite = NULL;
    map->res_x = 0;
    map->res_y = 0;
    map->r_floor = 0;
    map->g_floor = 0;
    map->b_floor = 0;
    map->r_ceiling = 0;
    map->g_ceiling = 0;
    map->b_ceiling = 0;
    map->player = 0;
    map->len_map = 0;
    map->len_line = 0;
    map->num_str = 0;
}