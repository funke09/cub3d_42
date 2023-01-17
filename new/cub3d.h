#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mlx.h>
#include "libft/libft.h"
# define MAX_X 2560
# define MAX_Y 1440


typedef struct s_game
{
    void *window;
    void *mlx;
    int width;
    int height;
}    t_game;

typedef struct s_map
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
    t_game game;
}       t_map;


void printerror(char *message);
int is_blank(char c);
void *free_loop(char **str);
int is_the_file(char *file);
void init_map(t_map *map);
void read_map(int fd, t_map *map);
int go_resolution(char *str, t_map *map);
int go_north(char *str, t_map *map);
int go_south(char *str, t_map *map);
int go_west(char *str, t_map *map);
int go_east(char *str, t_map *map);
int is_sprite(char *str, t_map *map);
int is_floorcolor(char *str, t_map *map);
int is_char(char **str, int *i);
int is_ceilingcolor(char *str, t_map *map);
int is_map(char *str);
int check_parametrs(char **str, t_map *map, int *count, int *i);
int check_first(char *str);
int check_player(t_map *map);
int if_no_or_multipule_player(t_map *map, char *str);
int map_is_protected(char **str);
int init_game(t_map *map);

#endif
