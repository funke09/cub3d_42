
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
# define MOUSE_R	6
# define MOUSE_L	7
# define MOUSE_R2	10
# define MOUSE_L2	9
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
	char	*img_data;
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

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		*map;
	t_player	*player;
	t_img		*image;

	void		*img;
	char		*img_data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	int			real_height;
	int			real_width;
	t_ray		v;
}	t_data;

void			ft_maloc_error(void *var);
void			ft_check_characters(t_data *data, t_map *map);
void			ft_map_init(char *map_path, t_data *data);
void			ft_map_errors(t_data *data, int error_num);
void			ft_check_walls(t_data *data, t_map *map);
void			ft_textures_init(t_data *data);
void			ft_render_minimap(t_data *data);
void			ft_draw_square(int y, int x, int size, t_data *data);
void			ft_render_player(t_data *data);
void			ft_update(t_data *data, int key);
void			ft_render_rays(t_data *data);
int				ft_is_in_wall(int new_x, int new_y, t_data *data);
t_ray			ft_horizontal_intersection(t_data *data, float ray_angle);
t_ray			ft_vertical_intersection(t_data *data, float ray_angle);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			ft_render(t_data *data, int key);
void			ft_draw_one_ray(t_data *data, float ray_angle, int size);
unsigned int	ft_trgb_to_dec(int t, int r, int g, int b);
void			ft_project_walls(t_data *data);
int				ft_get_color(char *color, int rgb);
float			ft_get_rot_angle(char c);
void			my_mlx_pixel_put2(t_data *data, int x, int y, int color_num);
void			ft_plyr_init(t_player *player, t_data *data);
void			ft_free_textures(t_data *data);
int				ft_exit_handler(void *n_data);
int				ft_key_handler(int key, void *n_data);
void			my_mlx_pixel_put_wall(t_data *data, int x, int y, int wall_top);
int				ft_verifie(char *file);
int				ft_strcmp(char *s1, char *s2);
int				ft_is_exist(char *str, char c);
int				ft_len_split(char **tab);
void			ft_free_split(char **tab);
void			ft_fill_data(t_map *data, char *file);
int				ft_is_flag(char *str);
int				ft_nbr_flag(char *str);
int				ft_is_gbr_valid(char *str);
float			ft_normalize_angle(float angle);

#endif
