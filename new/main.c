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
            if(file[i + 1] == 'c' && file[i + 2] == 'u' && file[i + 3] == 'b')
                return (0);
            else
                return (1);
        }
        i++;
    }
    return (1);
}



// map.cub
void init_map(t_map *map)
{
    // map = (t_map *)malloc(sizeof(t_map));
    if(!map)
        printerror("Error: malloc failed");
    map->tmp = malloc(sizeof(char *) * 2);
    if(!map->tmp || !map->tmp[0] || !map->tmp[1])
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
    int len;

    i = 0;
    j = 0;
    len = ft_strlen(str) + (number * 3);
    tmp = malloc(sizeof(char) * (len + 1));
    if(!tmp)
        printerror("Error: malloc failed");
    tmp[0] = '\0';
    while(i < ft_strlen(str))
    {
        if(str[i] == '\t')
        {
            tmp[j] = ' ';
            tmp[j + 1] = ' ';
            tmp[j + 2] = ' ';
            tmp[j + 3] = ' ';
            j += 4;
            // i++;
        }
        else
        {
            tmp[j] = str[i];
            j++;
        }
        i++;
    }
    tmp[j] = 0;
    free(str);
    return (tmp);
}

static int tab_counter(char *str, char c)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
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
            number = tab_counter(map->tmp[i], '\t');
            map->tmp[i] = (char*)ft_strreplace(map->tmp[i], number);
            if(!map->tmp[i])
                printerror("Error: replace failed");
        }
        i++;
    }
    return(i);
}

void read_map(int fd, t_map *map)
{
    char **tmp;
    int i;

    while((map->tmp[map->len_line] = get_next_line(fd)))
    {
        map->tmp[map->len_line][ft_strlen(map->tmp[map->len_line]) - 1] = '\0';
        i = 0;
        map->len_line += 1;
        tmp = malloc(sizeof(char *) * ((map->len_line) + 2));
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
    i = 0;
    if(!fill_space(map))
        printerror("Error: parsing failed .");
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
    printf("no = %s\n", map->no);
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
    // printf("str = %s\n", str);
    map->so = ft_strdup(str + i);
    if(!map->so)
        return (0);
    // printf("opeeen = %s\n", map->so);
    if(open(map->so, O_RDONLY) == -1)
    {
        // printf("map->so = %s | open failed\n", map->so);
        return (0);
    }
    // printf("so = %s\n", map->so);
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

int check_parametrs(char **str, t_map *map, int *count, int *i)
{
    while(str[*i] && (*count) < 8)
    {
        // printf("string[i] = %s\n", str[*i]);
        if(str[*i][0] == 'R' && str[*i][1] == ' ')
        {
            printf("resolution\n");
            if(!go_resolution(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'N' && str[*i][1] == 'O' && str[*i][2] == ' ')
        {
            printf("north\n");
            if(!go_north(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'S' && str[*i][1] == 'O' && str[*i][2] == ' ')
        {
            printf("south\n");
            // printf("string[i] = %s\n", str[*i]);
            if(!go_south(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'W' && str[*i][1] == 'E' && str[*i][2] == ' ')
        {
            printf("west\n");
            if(!go_west(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'E' && str[*i][1] == 'A' && str[*i][2] == ' ')
        {
            printf("east\n");
            if(!go_east(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'S' && str[*i][1] == ' ')
        {
            printf("sprite\n");
            if(!is_sprite(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'F' && str[*i][1] == ' ')
        {
            printf("floor\n");
            if(!is_floorcolor(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(str[*i][0] == 'C' && str[*i][1] == ' ')
        {
            printf("ceiling\n");
            if(!is_ceilingcolor(str[*i], map))
                return (0);
            (*count)++;
            (*i)++;
        }
        else if(!is_char(str, i))
        {
            printf("map\n");
            return (0);
        }
        else if(str[*i][0] == '\0')
            (*i)++;
    }
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
    int i;

    i = 0;
    while(str[0][i])
    {
        if (i + 1 > ft_strlen(str[0]))
            return (0);
        if(str[0][i] == '0' || str[0][i] == '2' || str[0][i] == 'N' || str[0][i] == 'S' || str[0][i] == 'W' || str[0][i] == 'E')
        {
            // printf("str[0] = %s\n", str[0]);
            // printf("str[-1][i + 1] = %c\n", str[-1][i + 1]);
            if(!str[-1][i - 1] || !str[-1][i] || !str[-1][i + 1] || !str[1][i - 1] || !str[1][i] || !str[1][i + 1] || !str[0][i - 1] || !str[0][i + 1])
            {
                // printf("str[-1] = %s\n", str[-1]);
                // printf("str[-1][i + 1] = %c\n", str[-1][i + 1]);
                // printf("i == %d\n", i);
                // printf("str[-1][i] = %c\n", str[-1][i]);
                // printf("str[1][i - 1] = %c\n", str[1][i - 1]);
                // printf("str[1][i] = %c\n", str[1][i]);
                // printf("str[1][i + 1] = %c\n", str[1][i + 1]);
                // printf("str[-1][i - 1] = %c\n", str[-1][i - 1]);
                // printf(">>>>>>>>>>str[0][i] = %c <<<<<<<\n", str[0][i]);
                // printf("str[0][i + 1] = %c\n", str[0][i + 1]);
                return (0);
            }
            // printf("we are here\n");
            if(is_blank(str[-1][i - 1]) || is_blank(str[-1][i]) || is_blank(str[-1][i + 1]) || is_blank(str[1][i - 1]) || is_blank(str[1][i]) || is_blank(str[1][i + 1]) || is_blank(str[0][i - 1]) || is_blank(str[0][i + 1]))
                return (0);
            // printf("we passed\n");
        }
        i++;
    }
    return (1);
}

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
        printf("END!");
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
            printf("*********map3\n");
            if(!map_is_protected(&str[i]))
                return(0);
            printf("*********map4\n");
            if(!if_no_or_multipule_player(map, str[i]))
                return(0);
        }
        i++;
    }
    printf("*********map5\n");
    if(!allocate_map(str, map))
        return (0);
    printf("*********END\n");
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
        printerror("Error: maap tmp failed\n");
    read_map(fd, map);
    printf("+++++++++++++");
    int i= 0 ;
    while (map->tmp[i])
    {
        printf("%s  len=%d\n", map->tmp[i], ft_strlen(map->tmp[i]));
        i++;
    }
    if(!parssing_map(map->tmp, map))
        printerror("Error: parsing failed");
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