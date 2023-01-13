#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mlx.h>
# define MAX_X 2560
# define MAX_Y 1440



typdef struct s_map
{
    char **map;
    char *no;
    char *so;
    char *we;
    char *ea;
    char *sprite;
    int res_x;
    int res_y;
    int r_floor;
    int g_floor;
    int b_floor;
    int r_ceiling;
    int g_ceiling;
    int b_ceiling;
    char player;
    int len_map;
    int len_line;
    int num_str;
    char    **tmp;
}       t_map;

#endif
