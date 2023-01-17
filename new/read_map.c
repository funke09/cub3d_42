#include "cub3d.h"

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