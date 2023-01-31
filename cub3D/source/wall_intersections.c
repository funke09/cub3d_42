
#include "cub3D.h"

// this function for know where the ray is facing 
void	ft_ray_facing(t_ray *v, float ray_angle, t_data *data)
{
	v->is_ray_facing_up = 0;
	v->is_ray_facing_down = 0;
	v->is_ray_facing_right = 0;
	v->is_ray_facing_left = 0;
	if (ray_angle > M_PI && ray_angle < 2 * M_PI)
		v->is_ray_facing_up = 1;
	if (v->is_ray_facing_up == 0)
		v->is_ray_facing_down = 1;
	if (ray_angle > M_PI * 0.5 && ray_angle < 1.5 * M_PI)
		v->is_ray_facing_left = 1;
	if (v->is_ray_facing_left == 0)
		v->is_ray_facing_right = 1;
	if (v->is_ray_facing_right == 1)
		data->player->is_ray_right = 1;
	else
		data->player->is_ray_right = 0;
	if (v->is_ray_facing_up == 1)
		data->player->is_ray_up = 1;
	else
		data->player->is_ray_up = 0;
}

// this function initialize the ft_horizontal_intersection() function vars
void	ft_init_horz_vars(t_data *data, float ray_angle, t_ray *v)
{
	v->y_intercept = floor(data->player->y / TILE_SIZE) * TILE_SIZE;
	if (v->is_ray_facing_down == 1)
		v->y_intercept += TILE_SIZE;
	v->x_intercept = data->player->x + \
	((v->y_intercept - data->player->y) / tan(ray_angle));
	v->y_steps = TILE_SIZE;
	if (v->is_ray_facing_up == 1)
		v->y_steps *= -1;
	v->x_steps = TILE_SIZE / tan(ray_angle);
	if (v->is_ray_facing_left == 1 && v->x_steps > 0)
		v->x_steps *= -1;
	if (v->is_ray_facing_right == 1 && v->x_steps < 0)
		v->x_steps *= -1;
	v->next_horz_touch_x = v->x_intercept;
	v->next_horz_touch_y = v->y_intercept;
	if (v->is_ray_facing_up == 1)
		v->next_horz_touch_y--;
	v->distance = sqrt(pow((v->y_intercept - data->player->y), 2) + \
	pow((v->y_intercept - data->player->y) / tan(ray_angle), 2));
	v->window_w = data->map->width * TILE_SIZE;
	v->window_h = data->map->height * TILE_SIZE;
}

// this function return the distance between the player
//  and the horizontal intersection with the wall
t_ray	ft_horizontal_intersection(t_data *data, float ray_angle)
{
	t_ray	v;

	ft_ray_facing(&v, ray_angle, data);
	ft_init_horz_vars(data, ray_angle, &v);
	while (v.next_horz_touch_x >= 0 && v.next_horz_touch_x < v.window_w
		&& v.next_horz_touch_y >= 0 && v.next_horz_touch_y < v.window_h)
	{
		if (ft_is_in_wall(v.next_horz_touch_x, v.next_horz_touch_y, data) == 1)
			return (v);
		v.next_horz_touch_x += v.x_steps;
		v.next_horz_touch_y += v.y_steps;
		v.distance += sqrt(pow(v.x_steps, 2) + pow(v.y_steps, 2));
	}
	v.distance = v.window_w * v.window_h;
	return (v);
}

// this function initialize the ft_vertical_intersection() function vars
void	ft_init_vertcl_vars(t_data *data, float ray_angle, t_ray *v)
{
	v->x_intercept = floor(data->player->x / TILE_SIZE) * TILE_SIZE;
	if (v->is_ray_facing_right == 1)
		v->x_intercept += TILE_SIZE;
	v->y_intercept = data->player->y + \
	((v->x_intercept - data->player->x) * tan(ray_angle));
	v->x_steps = TILE_SIZE;
	if (v->is_ray_facing_left == 1)
		v->x_steps *= -1;
	v->y_steps = TILE_SIZE * tan(ray_angle);
	if (v->is_ray_facing_up == 1 && v->y_steps > 0)
		v->y_steps *= -1;
	if (v->is_ray_facing_down == 1 && v->y_steps < 0)
		v->y_steps *= -1;
	v->next_vertcl_touch_x = v->x_intercept;
	v->next_vertcl_touch_y = v->y_intercept;
	if (v->is_ray_facing_left == 1)
		v->next_vertcl_touch_x--;
	v->distance = sqrt(pow((v->x_intercept - data->player->x), 2) + \
	pow((v->x_intercept - data->player->x) * tan(ray_angle), 2));
	v->window_w = data->map->width * TILE_SIZE;
	v->window_h = data->map->height * TILE_SIZE;
}

// this function return the distance between the player 
// and the vertical intersection with the wall
t_ray	ft_vertical_intersection(t_data *data, float ray_angle)
{
	t_ray	v;

	ft_ray_facing(&v, ray_angle, data);
	ft_init_vertcl_vars(data, ray_angle, &v);
	while (v.next_vertcl_touch_x >= 0 && v.next_vertcl_touch_x < v.window_w
		&& v.next_vertcl_touch_y >= 0 && v.next_vertcl_touch_y < v.window_h)
	{
		if (ft_is_in_wall(v.next_vertcl_touch_x, \
		v.next_vertcl_touch_y, data) == 1)
			return (v);
		v.next_vertcl_touch_x += v.x_steps;
		v.next_vertcl_touch_y += v.y_steps;
		v.distance += sqrt(pow(v.x_steps, 2) + pow(v.y_steps, 2));
	}
	v.distance = v.window_w * v.window_h;
	return (v);
}
