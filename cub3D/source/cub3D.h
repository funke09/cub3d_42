
#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# define TILE_SIZE 60
# define TEXTUR_WIDTH 50
# define TEXTUR_HEIGHTEIGHT 50

# define KEY_ESC	53
# define KEY_W	13
# define KEY_S	1
# define KEY_A	0
# define KEY_D	2
# define KEY_RIGHT	124
# define KEY_LEFT	123
# define RANDOM_KEY	9999999

typedef struct s_ray
{
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_right;
	int		is_ray_facing_left;

	float	x_intercept;
	float	y_intercept;
	float	x_steps;
	float	y_steps;

	float	next_vertcl_touch_x;
	float	next_vertcl_touch_y;
	float	ray_angle;
	int		window_w;
	int		window_h;
	float	distance;

	float	next_horz_touch_x;
	float	next_horz_touch_y;
}	t_ray;

typedef struct s_map
{
	char			**map;
	int				width;
	int				height;
	int				x_player;
	int				y_player;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			*floor_color;
	char			*ceil_color;
	unsigned int	floor_color_dc;
	unsigned int	ceil_color_dc;
}	t_map;

typedef struct s_player
{
	float	x;
	float	y;
	char	player_derection;
	int		is_ray_right;
	int		is_ray_up;
	int		is_horz_intr;
	float	turn_direction;
	float	walk_direction;
	float	rotate_angle;
	float	move_speed;
	float	rotation_speed;

	float	fov_angle;
	float	wall_strip_width;
	float	wall_strip_height;
	float	rays_num;
	float	minimap_scale_factor;
	int		minimap_size;
	int		sizeofplayer;
}	t_player;

typedef struct s_image
{
	void	*ptr;
	char	*img_var;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_image;

typedef struct s_imgs
{
	t_image		*no_texture;
	t_image		*so_texture;
	t_image		*we_texture;
	t_image		*ea_texture;
}	t_img;

typedef struct s_var
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		*map;
	t_player	*player;
	t_img		*image;

	void		*img;
	char		*img_var;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	int			real_height;
	int			real_width;
	t_ray		v;
}	t_var;

void			ft_erorr(void *var);
void			error_map(t_var *var, int error_num);
int				is_param(char *str);
void			is_characters(t_var *var, t_map *map);
int				param_number(char *str);
int				valid_color(char *str);
void			wall_checker(t_var *var, t_map *map);
void			init_map(char *map_path, t_var *var);
void			draw_square(int y, int x, int size, t_var *var);
int				has_wall(int new_x, int new_y, t_var *var, int front);
void			update(t_var *var, int key);
void			player_rendr(t_var *var);
void			render_rays(t_var *var);
void			render(t_var *var, int key);
void			init_texturs(t_var *var);
void			draw_pixel(t_var *var, int x, int y, int color);
t_ray			horizontal_intersection(t_var *var, float ray_angle);
t_ray			vertical_intersection(t_var *var, float ray_angle);
void			project_plane_wall(t_var *var);
void			put_one_ray(t_var *var, float ray_angle, int size);
unsigned int	convert_rgb_dec(int t, int r, int g, int b);
int				check_color(char *color, int rgb);
float			check_angle(char c);
void			init_player(t_player *player, t_var *var);
int				ft_destroy_window(void *n_var);
void			destroy_textures(t_var *var);
int				key_press(int key, void *n_var);
void			drawing_wall(t_var *var, int x, int y, int wall_top);
int				map_checker(char *file);
float			normalize(float angle);
int				count_tab(char **tab);
void			free_loop(char **tab);
void			get_info(t_map *var, char *file);
int				ft_strcmp(char *s1, char *s2);
void			drawing_ceil_floor(t_var *var, int x, int y, int color_num);

#endif
