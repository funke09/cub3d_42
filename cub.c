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

int read_file(char *file, t_cub3d *cub3d)
{
    int fd;
    char *line;
    // int ret;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        cub3d_error("Invalid file");
    while ((line = get_next_line(fd)))
    {
        if (line[0] == 'R')
            cub3d_parse_resolution(cub3d, line);
        else if (line[0] == 'N' && line[1] == 'O')
            cub3d_parse_texture(cub3d, line, &cub3d->no);
        else if (line[0] == 'S' && line[1] == 'O')
            cub3d_parse_texture(cub3d, line, &cub3d->so);
        else if (line[0] == 'W' && line[1] == 'E')
            cub3d_parse_texture(cub3d, line, &cub3d->we);
        else if (line[0] == 'E' && line[1] == 'A')
            cub3d_parse_texture(cub3d, line, &cub3d->ea);
        else if (line[0] == 'S')
            cub3d_parse_texture(cub3d, line, &cub3d->s);
        else if (line[0] == 'F')
            cub3d_parse_color(cub3d, line, &cub3d->f);
        else if (line[0] == 'C')
            cub3d_parse_color(cub3d, line, &cub3d->c);
        else if (line[0] == '1')
            cub3d_parse_map(cub3d, line);
        else
            cub3d_error("Invalid file");
        free(line);
    }
    if(!line)
        cub3d_error("Invalid file");
    close(fd);
    return (1);
}

int main(int ac, char **av)
{
    int check;
    t_cub3d *cub3d;

    cub3d = NULL;
    if(ac != 2)
        printerror("Error: usage ./cub3d map.cub");
    check_filename(av[1]);
    check = read_file(av[1], cub3d);
}