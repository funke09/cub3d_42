#include "cub3d.h"

int cub3d_error(char *msg)
{
    ft_putstr_fd(msg, 2);
    exit(1);
}

void cub3d_parse_resolution(t_cub3d *cub3d, char *line)
{
    int i;

    (void)cub3d;
    i = 1;
    while (line[i] == ' ')
        i++;
    cub3d->width = ft_atoi(line + i);
    while (line[i] >= '0' && line[i] <= '9')
        i++;
    while (line[i] == ' ')
        i++;
    cub3d->height = ft_atoi(line + i);
}

void cub3d_parse_texture(t_cub3d *cub3d, char *line, char **texture)
{
    int i;

    (void)cub3d;
    i = 1;
    while (line[i] == ' ')
        i++;
    *texture = ft_strdup(line + i);
}

void cub3d_parse_color(t_cub3d *cub3d, char *line, int *color)
{
    int i;
    int r;
    int g;
    int b;

    (void)cub3d;
    i = 1;
    while (line[i] == ' ')
        i++;
    r = ft_atoi(line + i);
    while (line[i] >= '0' && line[i] <= '9')
        i++;
    while (line[i] == ' ')
        i++;
    g = ft_atoi(line + i);
    while (line[i] >= '0' && line[i] <= '9')
        i++;
    while (line[i] == ' ')
        i++;
    b = ft_atoi(line + i);
   /* It's a bitwise operation. */
    *color = (r << 16) | (g << 8) | b;
}

int is_valid_char(char c)
{
    if (c == '0' || c == '1' || c == '\n' || c == 'N' || c == 'S' || c == 'E' || c == ' ')
        return (1);
    return (0);
}

void cub3d_parse_map(t_cub3d *cub3d, char *line)
{
    int i;

    (void)cub3d;
    i= 0;
    if(line[0] != '1')
        cub3d_error("Invalid map: first line must be a wall");
    while(line[i])
    {
        if(!is_valid_char(line[i]))
            cub3d_error("Invalid map: invalid char");
    }
}

// void cub3d_parse(t_cub3d *cub3d, char *path)
// {
//     int fd;
//     char *line;
//     // int ret;

//     fd = open(path, O_RDONLY);
//     if (fd == -1)
//         cub3d_error("Invalid file");
//     while ((line = get_next_line(fd)))
//     {
//         if (line[0] == 'R')
//             cub3d_parse_resolution(cub3d, line);
//         else if (line[0] == 'N' && line[1] == 'O')
//             cub3d_parse_texture(cub3d, line, &cub3d->no);
//         else if (line[0] == 'S' && line[1] == 'O')
//             cub3d_parse_texture(cub3d, line, &cub3d->so);
//         else if (line[0] == 'W' && line[1] == 'E')
//             cub3d_parse_texture(cub3d, line, &cub3d->we);
//         else if (line[0] == 'E' && line[1] == 'A')
//             cub3d_parse_texture(cub3d, line, &cub3d->ea);
//         else if (line[0] == 'S')
//             cub3d_parse_texture(cub3d, line, &cub3d->s);
//         else if (line[0] == 'F')
//             cub3d_parse_color(cub3d, line, &cub3d->f);
//         else if (line[0] == 'C')
//             cub3d_parse_color(cub3d, line, &cub3d->c);
//         else if (line[0] == '1')
//             cub3d_parse_map(cub3d, line);
//         else
//             cub3d_error("Invalid file");
//         free(line);
//     }
//     if(!line)
//         cub3d_error("Invalid file");
//     close(fd);
// }

// int main(int argc, char **argv)
// {
//     t_cub3d cub3d;

//     if (argc == 2)
//     {
//         cub3d_parse(&cub3d, argv[1]);
//     }
//     else
//         cub3d_error("Invalid number of arguments");
//     return (0);
// }