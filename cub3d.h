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
    char    *s;
    int     f;
    int     c;
    char    **map;
}	t_cub3d;

#endif