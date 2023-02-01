
#include "cub3D.h"

// this function initialize one texture
void	init_texturs_utile(t_data *data, int txtr_nbr, char *txtr_path)
{
	void	*p;
	int		s;
	t_image	*texture;

	p = data->mlx_ptr;
	texture = (t_image *)malloc(sizeof(t_image));
	texture->ptr = mlx_xpm_file_to_image(p, txtr_path, &s, &s);
	if (!texture->ptr)
	{
		destroy_textures(data);
		error_map(data, 5);
	}
	texture->img_data = mlx_get_data_addr(texture->ptr, \
	&texture->bits_per_pixel, &texture->line_size, &texture->endian);
	if (txtr_nbr == 1)
		data->image->ea_texture = texture;
	else if (txtr_nbr == 2)
		data->image->we_texture = texture;
	else if (txtr_nbr == 3)
		data->image->no_texture = texture;
	else if (txtr_nbr == 4)
		data->image->so_texture = texture;
}

// this function initialize all textures.
void	init_texturs(t_data *data)
{
	t_img	*image;
	t_map	*map;

	image = data->image;
	map = data->map;
	init_texturs_utile(data, 1, map->ea_texture);
	init_texturs_utile(data, 2, map->we_texture);
	init_texturs_utile(data, 3, map->no_texture);
	init_texturs_utile(data, 4, map->so_texture);
}

// this function helps you redraw the map element on the minimap
int	ft_get_position_color(t_data *data, int x, int y, int map_size)
{
	int	s_y;
	int	s_x;

	s_y = data->player->y - map_size / 2;
	s_x = data->player->x - map_size / 2;
	if (has_wall(s_x + x, s_y + y, data) == 1
		|| data->map->map[(s_y + y) / 50][(s_x + x) / 50] == ' ')
		return (0x808080);
	return (0xffffff);
}

// this function render the game elements
// Note: 
// you will find the function ft_render_minimap() that render the map 
// in the render_rays() ==> ft_cast_rays()
void	render(t_data *data, int key)
{
	update(data, key);
	project_plane_wall(data);
}
