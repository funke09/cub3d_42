#include "cub3d.h"

int cub3d_error(char *msg)
{
    ft_putstr_fd(msg, 2);
    exit(1);
}

void cub3d_parse_resolution(t_cub3d *cub3d, char *line)
{
   int i;
   int flag;

   i = 1;
   flag = 0;
   while(line[i] == ' ')
       i++;
    while(is_digit(line[i]) && flag == 0)
    {
        cub3d->width = ft_atoi(line + i);
        flag = 1;
        i++;
    }
    while(line[i] == ' ')
        i++;
    while(is_digit(line[i]) && flag == 1)
    {
        cub3d->height = ft_atoi(line + i);
        flag = 2;
        i++;
    }
    if(flag != 2)
        cub3d_error("Error: invalid resolution");
}


int is_xpm(char *line)
{
    int i;

    i = ft_strlen(line) - 1;
    if(line[i] == 'm' && line[i - 1] == 'p' && line[i - 2] == 'x' && line[i - 3] == '.')
        return (1);
    return (0);
}

void cub3d_check_duplicate_path(t_cub3d *cub3d, int num)
{
    if(num == 1 && cub3d->no)
        cub3d_error("Error: duplicate path");
    else if(num == 2 && cub3d->so)
        cub3d_error("Error: duplicate path");
    else if(num == 3 && cub3d->we)
        cub3d_error("Error: duplicate path");
    else if(num == 4 && cub3d->ea)
        cub3d_error("Error: duplicate path");
    else if(num == 5 && cub3d->sprite)
        cub3d_error("Error: duplicate path");
}

void check_duplicate_texture(t_cub3d *cub3d)
{
    if(!cub3d->no)
        cub3d_error("Error: missing texture");
    else if(!cub3d->so)
        cub3d_error("Error: missing texture");
    else if(!cub3d->we)
        cub3d_error("Error: missing texture");
    else if(!cub3d->ea)
        cub3d_error("Error: missing texture");
    else if(!cub3d->sprite)
        cub3d_error("Error: missing texture");
}

void cub3d_parse_texture(t_cub3d *cub3d, char *line, int num)
{
    int i;
    int j;
    char *path;

    i = 2;
    j = 0;
    if(!line[i])
        cub3d_error("Error: invalid texture path");
    while(line[i] == ' ')
        i++;
    path = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
    if(!path)
        cub3d_error("Error: malloc failed");
    while(line[i])
    {
        path[j] = line[i];
        i++;
        j++;
    }
    path[j] = '\0';
    if(!is_xpm(path))
        cub3d_error("Error: invalid texture path");
    cub3d_check_duplicate_path(cub3d, num);
    if(num == 1)
        cub3d->no = path;
    else if(num == 2)
        cub3d->so = path;
    else if(num == 3)
        cub3d->we = path;
    else if(num == 4)
        cub3d->ea = path;
    else if(num == 5)
        cub3d->sprite = path;
    check_duplicate_texture(cub3d); 
}

void cub3d_parse_color(t_cub3d *cub3d, char *line, int *color)
{
    int i;
    int j;
    int flag;
    int rgb[3];

    i = 1;
    j = 0;
    flag = 0;
    while(line[i] == ' ')
        i++;
    while(is_digit(line[i]) && flag < 3)
    {
        rgb[flag] = ft_atoi(line + i);
        flag++;
        i++;
        while(is_digit(line[i]))
            i++;
        if(line[i] == ',')
            i++;
    }
    if(flag != 3)
        cub3d_error("Error: invalid color");
  /* Converting the rgb values into a single integer. */
    *color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}

int is_valid_char(char c)
{
    if (c == '0' || c == '1' || c == '\n' || c == 'N' || c == 'S' || c == 'E' || c == ' ')
        return (1);
    return (0);
}

int is_map(char *str)
{
    if(*str == '\0')
        return (0);
    while (*str)
    {
        if(!is_space(*str) && !ft_strchr(IS_CHAR, *str))
            return (0);
        str++;
    }
    return (1);
}

void cub3d_parse_map(t_cub3d *cub3d, char *line)
{
    while (is_map())
    {
        /* code */
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