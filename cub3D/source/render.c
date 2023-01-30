
#include "cub3D.h"

// this function initialize one texture
void	ft_textures_init_utile(t_data *data, int txtr_nbr, char *txtr_path)
{
	void	*p;
	int		s;
	t_image	*texture;

	p = data->mlx_ptr;
	texture = (t_image *)malloc(sizeof(t_image));
	texture->pointer = mlx_xpm_file_to_image(p, txtr_path, &s, &s);
	if (!texture->pointer)
	{
		ft_free_textures(data);
		ft_map_errors(data, 5);
	}
	texture->img_data = mlx_get_data_addr(texture->pointer, \
	&texture->bits_per_pixel, &texture->line_size, &texture->endian);
	if (txtr_nbr == 1)
		data->obj_img->ea_texture = texture;
	else if (txtr_nbr == 2)
		data->obj_img->we_texture = texture;
	else if (txtr_nbr == 3)
		data->obj_img->no_texture = texture;
	else if (txtr_nbr == 4)
		data->obj_img->so_texture = texture;
}

// this function initialize all textures.
void	ft_textures_init(t_data *data)
{
	t_img	*obj_img;
	t_map	*obj_map;

	obj_img = data->obj_img;
	obj_map = data->obj_map;
	ft_textures_init_utile(data, 1, obj_map->ea_texture_path);
	ft_textures_init_utile(data, 2, obj_map->we_texture_path);
	ft_textures_init_utile(data, 3, obj_map->no_texture_path);
	ft_textures_init_utile(data, 4, obj_map->so_texture_path);
}

// this function helps you redraw the map element on the minimap
int	ft_get_position_color(t_data *data, int x, int y, int map_size)
{
	int	s_y;
	int	s_x;

	s_y = data->obj_plyr->y - map_size / 2;
	s_x = data->obj_plyr->x - map_size / 2;
	if (ft_is_in_wall(s_x + x, s_y + y, data) == 1
		|| data->obj_map->map[(s_y + y) / 50][(s_x + x) / 50] == ' ')
		return (0x808080);
	return (0xffffff);
}


// this function render the minimap
void	ft_render_minimap(t_data *data)
{
	int		y;
	int		x;
	int		map_size;

	map_size = data->obj_plyr->minimap_size;
	y = -1;
	while (++y < map_size)
	{
		x = -1;
		while (++x < map_size)
		{
			my_mlx_pixel_put(data, x, y, \
				ft_get_position_color(data, x, y, map_size));
		}
	}
}

// this function render the game elements
// Note: 
// you will find the function ft_render_minimap() that render the map 
// in the ft_render_rays() ==> ft_cast_rays()
void	ft_render(t_data *data, int key)
{
	ft_update(data, key);
	ft_project_walls(data);
}
