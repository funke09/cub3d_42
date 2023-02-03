/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:41:07 by zcherrad          #+#    #+#             */
/*   Updated: 2023/02/03 15:52:43 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# define TILE_SIZE 50
# define TEXTUR_WIDTH 50
# define TEXTUR_HEIGHT 50

# define KEY_ESC	53
# define KEY_W	13
# define KEY_S	1
# define KEY_A	0
# define KEY_D	2
# define KEY_RIGHT	124
# define KEY_LEFT	123
# define RANDOM_KEY	-404

/*A struct that contains all the information about the ray. */
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

/* A struct that contains all the information about the map.*/
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

/* A struct that contains all the information about the player. */
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
	int		minimap_size;
	int		sizeofplayer;
}	t_player;

/* A struct that contains all the information about the image. */
typedef struct s_image
{
	void	*ptr;
	char	*img_var;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_image;

/*A struct that contains all the information about the image. */
typedef struct s_imgs
{
	t_image		*no_texture;
	t_image		*so_texture;
	t_image		*we_texture;
	t_image		*ea_texture;
}	t_img;

/* A struct that contains all the information about the game. */
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

// Parssing functions needed
void			ft_erorr(void *var);
char			*dup_cub(char *s1, int len);
int				ft_strcmp(char *s1, char *s2);
int				count_tab(char **tab);
void			free_loop(char **tab);
void			error_map(t_var *var, int error_num);
int				is_param(char *str);
void			is_characters(t_var *var, t_map *map);
int				param_number(char *str);
int				valid_color(char *str);
int				map_checker(char *file);
void			get_info(t_map *var, char *file);
void			init_map(char *map_path, t_var *var);

// execution functions needed
void			init_texturs(t_var *var);
t_ray			horizontal_intersection(t_var *var, float ray_angle);
t_ray			vertical_intersection(t_var *var, float ray_angle);
void			project_plane_wall(t_var *var);
unsigned int	convert_rgb_dec(int t, int r, int g, int b);
void			wall_checker(t_var *var, t_map *map);
int				check_color(char *color, int rgb);
float			normalize(float angle);
float			check_angle(char c);
void			init_player(t_player *player, t_var *var);

//drawing and rendering 3D functions 
int				ft_destroy_window(void *n_var);
void			destroy_textures(t_var *var);
void			render(t_var *var, int key);
int				key_press(int key, void *n_var);
int				has_wall(int new_x, int new_y, t_var *var, int front);
void			update(t_var *var, int key);
void			render_rays(t_var *var);
void			drawing_wall(t_var *var, int x, int y, int first_wall);
void			drawing_ceil_floor(t_var *var, int x, int y, int number);
void			move_left(t_player *player, float fixedangle,
					float *new_x, float *new_y);
void			move_right(t_player *player, float fixedangle,
					float *new_x, float *new_y);
void			update_playe(t_player *player, float x, float y);
void			change_angle(t_player *player);
void			change_x_y(t_player *player, float *move_step,
					float *new_x, float *new_y);
#endif
