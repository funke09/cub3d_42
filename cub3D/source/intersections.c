
#include "cub3D.h"

// this function for know where the ray is facing 
void	ft_ray_facing(t_ray *v, float ray_angle, t_var *var)
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
		var->player->is_ray_right = 1;
	else
		var->player->is_ray_right = 0;
	if (v->is_ray_facing_up == 1)
		var->player->is_ray_up = 1;
	else
		var->player->is_ray_up = 0;
}

// this function initialize the horizontal_intersection() function vars
void	ft_init_horz_vars(t_var *var, float ray_angle, t_ray *v)
{
	v->y_intercept = floor(var->player->y / TILE_SIZE) * TILE_SIZE;
	if (v->is_ray_facing_down == 1)
		v->y_intercept += TILE_SIZE;
	v->x_intercept = var->player->x + \
	((v->y_intercept - var->player->y) / tan(ray_angle));
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
	v->distance = sqrt(pow((v->y_intercept - var->player->y), 2) + \
	pow((v->y_intercept - var->player->y) / tan(ray_angle), 2));
	v->window_w = var->map->width * TILE_SIZE;
	v->window_h = var->map->height * TILE_SIZE;
}

// this function return the distance between the player
//  and the horizontal intersection with the wall
t_ray	horizontal_intersection(t_var *var, float ray_angle)
{
	t_ray	v;

	ft_ray_facing(&v, ray_angle, var);
	ft_init_horz_vars(var, ray_angle, &v);
	while (v.next_horz_touch_x >= 0 && v.next_horz_touch_x < v.window_w
		&& v.next_horz_touch_y >= 0 && v.next_horz_touch_y < v.window_h)
	{
		if (has_wall(v.next_horz_touch_x, v.next_horz_touch_y, var, 99) == 1)
			return (v);
		v.next_horz_touch_x += v.x_steps;
		v.next_horz_touch_y += v.y_steps;
		v.distance += sqrt(pow(v.x_steps, 2) + pow(v.y_steps, 2));
	}
	v.distance = v.window_w * v.window_h;
	return (v);
}

// this function initialize the vertical_intersection() function vars
void	ft_init_vertcl_vars(t_var *var, float ray_angle, t_ray *v)
{
	v->x_intercept = floor(var->player->x / TILE_SIZE) * TILE_SIZE;
	if (v->is_ray_facing_right == 1)
		v->x_intercept += TILE_SIZE;
	v->y_intercept = var->player->y + \
	((v->x_intercept - var->player->x) * tan(ray_angle));
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
	v->distance = sqrt(pow((v->x_intercept - var->player->x), 2) + \
	pow((v->x_intercept - var->player->x) * tan(ray_angle), 2));
	v->window_w = var->map->width * TILE_SIZE;
	v->window_h = var->map->height * TILE_SIZE;
}

// this function return the distance between the player 
// and the vertical intersection with the wall
t_ray	vertical_intersection(t_var *var, float ray_angle)
{
	t_ray	v;

	ft_ray_facing(&v, ray_angle, var);
	ft_init_vertcl_vars(var, ray_angle, &v);
	while (v.next_vertcl_touch_x >= 0 && v.next_vertcl_touch_x < v.window_w
		&& v.next_vertcl_touch_y >= 0 && v.next_vertcl_touch_y < v.window_h)
	{
		if (has_wall(v.next_vertcl_touch_x, \
		v.next_vertcl_touch_y, var, 99) == 1)
			return (v);
		v.next_vertcl_touch_x += v.x_steps;
		v.next_vertcl_touch_y += v.y_steps;
		v.distance += sqrt(pow(v.x_steps, 2) + pow(v.y_steps, 2));
	}
	v.distance = v.window_w * v.window_h;
	return (v);
}
