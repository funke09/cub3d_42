#include "cub3d.h"

void printerror(char *message)
{
    ft_putendl_fd(message, STDERR_FILENO);
    exit(EXIT_FAILURE);
}

void check_filename(char *filename)
{
    int len;

    len = ft_strlen(filename);
    if(len <= 4)
        printerror("Error: filename too short (missed filename.cub)");
    if(ft_strncmp(filename + len - 4, ".cub", 4))
        printerror("Error: wrong file extension (must be .cub)");
}

// function that take the 6 argiments in the file and stored them in the struct
int read_file(char *file, t_cub3d *cub3d)
{
    char *line;
    int i;

    i = 0;
    cub3d->fd = open(file, O_RDONLY);
    if(cub3d->fd == -1)
        printerror("Error: can't open file");
    while((line = get_next_line(cub3d->fd)))
    {
        if(line[0] == 'R')
            cub3d_parse_resolution(cub3d, line);
        else if(line[0] == 'N' && line[1] == 'O')
            cub3d_parse_texture(cub3d, line,1);
        else if(line[0] == 'S' && line[1] == 'O')
            cub3d_parse_texture(cub3d, line, 2);
        else if(line[0] == 'W' && line[1] == 'E')
            cub3d_parse_texture(cub3d, line,3);
        else if(line[0] == 'E' && line[1] == 'A')
            cub3d_parse_texture(cub3d, line, 4);
        else if(line[0] == 'S' && line[1] == ' ')
            cub3d_parse_texture(cub3d, line, 5);
        else if(line[0] == 'F' && line[1] == ' ')
            cub3d_parse_color(cub3d, line, &cub3d->color_f);
        else if(line[0] == 'C' && line[1] == ' ')
            cub3d_parse_color(cub3d, line, &cub3d->color_c);
        else if(is_valid_char(line[0]))
            cub3d_parse_map(cub3d, line);
        else
            printerror("Error: invalid information in the file\n");
        free(line);
    }
    close(cub3d->fd);
    return (1);
}

// function that get the len of the bigger line in the map
int get_map_len(char **map)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while(map[i])
    {
        if(ft_strlen(map[i]) > len)
            len = ft_strlen(map[i]);
        i++;
    }
    return (len);
}

// function that read from file and stored the map in a 2d array
void read_map(t_cub3d *cub3d, char *line)
{
    int i;
    int j;
    int len;
    char **map;

    i = 0;
    j = 0;
    len = get_map_len(cub3d->map);
    map = (char **)malloc(sizeof(char *) * (ft_strlen(line) + 1));
    while(line[i])
    {
        if(line[i] == ' ')
        {
            map[j] = (char *)malloc(sizeof(char) * (len + 1));
            ft_strlcpy(map[j], line, len + 1);
            j++;
        }
        i++;
    }
    map[j] = NULL;
    cub3d->map = map;
}

void init_cub3d(t_cub3d *cub3d)
{
    cub3d->height = 0;
    cub3d->width = 0;
    cub3d->no = NULL;
    cub3d->so = NULL;
    cub3d->we = NULL;
    cub3d->ea = NULL;
    cub3d->sprite = NULL;
    cub3d->color_f = 0;
    cub3d->color_c = 0;
    cub3d->map = NULL;

}

int main(int ac, char **av)
{
    int check;
    t_cub3d *cub3d;

    cub3d = NULL;
    if(ac != 2)
        printerror("Error: usage ./cub3d map.cub");
    check_filename(av[1]);
    init_cub3d(cub3d);
    check = read_file(av[1], cub3d);
}