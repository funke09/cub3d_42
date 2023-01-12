#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "mlx.h"
# include "libft/libft.h"


# define RIGHT_KEY 124
# define UP_KEY 126
# define DOWN_KEY 125
# define A_KEY  0
# define S_KEY  1
# define D_KEY  2
# define W_KEY  13
# define ESC 53
# define IS_CHAR "012NSEW"

typedef struct s_cub3d
{
    void	*mlx;
    void	*win;
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;



    
    int     width;
    int     height;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    char    *sprite;
    int     color_f;
    int     color_c;
    int     fd;
    char    **map;
}	t_cub3d;


int cub3d_error(char *msg);
void cub3d_parse_resolution(t_cub3d *cub3d, char *line);
void cub3d_parse_texture(t_cub3d *cub3d, char *line, int num);
void cub3d_parse_color(t_cub3d *cub3d, char *line, int *color);
int is_valid_char(char c);
void cub3d_parse_map(t_cub3d *cub3d, char *line);

#endif