#include "cub3d.h"
void printerror(char *message)
{
    printf("%s\n", message);
    exit(1);
}

void free_loop(char **str)
{
    int i;

    i = 0;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

int is_the_file(char *file)
{
    int i;

    i = ft_strlen(file) - 1;
    if(file[i] == 'b' && file[i - 1] == 'u' && file[i - 2] == 'c' && file[i - 3] == '.')
        return (1);
    return (0);
}

void init_map(t_map *map)
{
    map->tmp = malloc(2);
    if(!map->tmp)
        printerror("Error: malloc failed");
    map->tmp[0] = 0;
    map->tmp[1] = 0;
    map->map = NULL;
    map->no = NULL;
    map->so = NULL;
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
// to realloc tabs we add 4 cause we need to add 4 spaces
void *ft_strreplace(char *str, int number)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    j = 0;

    tmp = malloc(sizeof(char) * (ft_strlen(str) + 4));
    if(!tmp)
        printerror("Error: malloc failed");
    
    while(str[i])
    {
        if(i == number)
        {
            tmp[j] = ' ';
            tmp[j + 1] = ' ';
            tmp[j + 2] = ' ';
            tmp[j + 3] = ' ';
            j += 4;
            i++;
        }
        tmp[j] = str[i];
        i++;
        j++;
    }
    tmp[j] = 0;
    free(str);
    return (tmp);
}

int fill_space(t_map *map)
{
    int i;
    int number;

    i = 0;
    while(map->tmp[i])
    {
        if(ft_strchr(map->tmp[i], '\t'))
        {
            number = ft_strchr(map->tmp[i], '\t') - map->tmp[i];
            map->tmp[i] = ft_strreplace(map->tmp[i], number);
            if(!map->tmp[i])
                printerror("Error: replace failed");
        }
        i++;
    }
    return(i);
}

void read_map(int fd, t_map *map)
{
    while(get_next_line(fd, &(map->tmp[map->len_line])) > 0)
    {
        char **tmp;
        int i;

        i = 0;
        map->len_line++;
        tmp = malloc(sizeof(char *) * (map->len_line + 2));
        if(!tmp)
            printerror("Error: malloc failed");
        while(map->tmp[i])
        {
            tmp[i] = map->tmp[i];
            i++;
        }
        tmp[map->len_line] = 0;
        tmp[map->len_line + 1] = 0;
        free(map->tmp);
        map->tmp = tmp;
    }
    if(!fill_space(map))
        printerror("Error: parsing failed");
}

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

int check_params(char **str, t_map *map, int *count, int *i)
{
    while(str[*i])
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
        }
        else if(str[*i][0] == 'S' && str[*i][1] == 'O' && str[*i][2] == ' ')
        {  
        }
        else if(str[*i][0] == 'W' && str[*i][1] == 'E' && str[*i][2] == ' ')
        {  
        }
        else if(str[*i][0] == 'E' && str[*i][1] == 'A' && str[*i][2] == ' ')
        {
        }
        else if(str[*i][0] == 'S' && str[*i][1] == ' ')
        {
        }
        else if(str[*i][0] == 'F' && str[*i][1] == ' ')
        {
        }
        else if(str[*i][0] == 'C' && str[*i][1] == ' ')
        {
        }
        else if(str[*i][0] == '1' || str[*i][0] == '0' || str[*i][0] == '2')
            return (1);
        else
            return (0);
        (*i)++;
}


int parssing_map(char **str, t_map *map)
{
    int i;
    int count;

    i = 0;
    count = 0;
    if(!check_parametrs(str, map, &count, &i))
        return (0);
}


int sumilation(char *file_name)
{
    int fd;
    t_map *map;

    init_map(map);
    fd = open(file_name, O_RDONLY);
    if(fd <= 0)
        printerror("Error: invalid file");
    read_map(fd, map);
    if(!parssing_map(&map->tmp, map))
        printerror("Error: parsing failed");
    
}

int main(int ac, char **av)
{
    if(ac == 2)
    {
        if(is_the_file(av[1]))
            printerror("Error: invalid file");
        if(sumilation(av[1]))
            printerror("Error: invalid map");
    }
    else
       printerror("Error: usage ./cub3d map.cub");
}