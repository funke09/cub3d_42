
#include "cub3D.h"

void	ft_drawer_init(t_data *data)
{
	int		s;
	void	*p;

	s = COLUMN_SIZE;
	p = data->mlx_ptr;
	data->obj_img->ea_texture = mlx_xpm_file_to_image(p, data->obj_map->ea_texture_path, &s, &s);
	data->obj_img->we_texture = mlx_xpm_file_to_image(p, data->obj_map->we_texture_path, &s, &s);
	data->obj_img->no_texture = mlx_xpm_file_to_image(p, data->obj_map->no_texture_path, &s, &s);
	data->obj_img->so_texture = mlx_xpm_file_to_image(p, data->obj_map->so_texture_path, &s, &s);
}

void	ft_put_image(t_data *data, void	*img, int y, int x)
{
	void	*w;
	void	*p;

	w = data->win_ptr;
	p = data->mlx_ptr;
	mlx_put_image_to_window(p, w, img, x * 50, y * 50);
}

void	ft_render_map(t_data *data)
{
	int		y;
	int		x;
	char	**map;
	t_map	*obj_map;

	obj_map = data->obj_map;
	map = data->obj_map->map;
	y = -1;
	while (++y < obj_map->map_height)
	{
		x = -1;
		while (++x < obj_map->map_width)
		{
			if (obj_map->map[y][x] == '1')
				ft_put_image(data, data->obj_img->ea_texture, y, x);
			else if (obj_map->map[y][x] == '0' || obj_map->map[y][x] == 'W' || obj_map->map[y][x] == 'E' || obj_map->map[y][x] == 'N' || obj_map->map[y][x] == 'S')
				ft_put_image(data, data->obj_img->no_texture, y, x);
		}
	}
}
