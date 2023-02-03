
#include "cub3D.h"

/**
 * It sets the ray's direction
 * 
 * @param ray the ray we're casting
 * @param ray_angle the angle of the ray in radians
 * @param var the structure that contains all the variables of the game.
 */
void	facing_of_ray(t_ray *ray, float ray_angle, t_var *var)
{
	ray->is_ray_facing_up = 0;
	ray->is_ray_facing_down = 0;
	ray->is_ray_facing_right = 0;
	ray->is_ray_facing_left = 0;
	if (ray_angle > M_PI && ray_angle < 2 * M_PI)
		ray->is_ray_facing_up = 1;
	if (ray->is_ray_facing_up == 0)
		ray->is_ray_facing_down = 1;
	if (ray_angle > M_PI * 0.5 && ray_angle < 1.5 * M_PI)
		ray->is_ray_facing_left = 1;
	if (ray->is_ray_facing_left == 0)
		ray->is_ray_facing_right = 1;
	if (ray->is_ray_facing_right == 1)
		var->player->is_ray_right = 1;
	else
		var->player->is_ray_right = 0;
	if (ray->is_ray_facing_up == 1)
		var->player->is_ray_up = 1;
	else
		var->player->is_ray_up = 0;
}


/**
 * It initializes the horizontal ray
 * 
 * @param global the global variable structure
 * @param angle the angle of the ray in radians
 * @param ray the ray that we're currently casting
 */
void	init_horizontal(t_var *global, float angle, t_ray *ray)
{
	ray->y_intercept = floor(global->player->y / TILE_SIZE) * TILE_SIZE;
	if (ray->is_ray_facing_down == 1)
		ray->y_intercept += TILE_SIZE;
	ray->x_intercept = global->player->x + \
	((ray->y_intercept - global->player->y) / tan(angle));
	ray->y_steps = TILE_SIZE;
	if (ray->is_ray_facing_up == 1)
		ray->y_steps *= -1;
	ray->x_steps = TILE_SIZE / tan(angle);
	if (ray->is_ray_facing_left == 1 && ray->x_steps > 0)
		ray->x_steps *= -1;
	if (ray->is_ray_facing_right == 1 && ray->x_steps < 0)
		ray->x_steps *= -1;
	ray->next_horz_touch_x = ray->x_intercept;
	ray->next_horz_touch_y = ray->y_intercept;
	if (ray->is_ray_facing_up == 1)
		ray->next_horz_touch_y--;
	ray->distance = sqrt(pow((ray->y_intercept - global->player->y), 2) + \
	pow((ray->y_intercept - global->player->y) / tan(angle), 2));
	ray->window_w = global->map->width * TILE_SIZE;
	ray->window_h = global->map->height * TILE_SIZE;
}


/**
 * It finds the first wall that the ray hits, and returns the distance to that wall
 * 
 * @param global a pointer to the global variable struct
 * @param ray_angle the angle of the ray we're currently casting
 * 
 * @return A ray struct.
 */
t_ray	horizontal_intersection(t_var *global, float ray_angle)
{
	t_ray	ray;

	facing_of_ray(&ray, ray_angle, global);
	init_horizontal(global, ray_angle, &ray);
	while (ray.next_horz_touch_x >= 0 && ray.next_horz_touch_x < ray.window_w
		&& ray.next_horz_touch_y >= 0 && ray.next_horz_touch_y < ray.window_h)
	{
		if (has_wall(ray.next_horz_touch_x, ray.next_horz_touch_y, global, 99) == 1)
			return (ray);
		ray.next_horz_touch_x += ray.x_steps;
		ray.next_horz_touch_y += ray.y_steps;
		ray.distance += sqrt(pow(ray.x_steps, 2) + pow(ray.y_steps, 2));
	}
	ray.distance = ray.window_w * ray.window_h;
	return (ray);
}


/**
 * It initializes the vertical ray
 * 
 * @param global a pointer to the global variable struct
 * @param ray_angle The angle of the ray relative to the player's direction.
 * @param ray the ray that we're currently casting
 */
void	init_vertical(t_var *global, float ray_angle, t_ray *ray)
{
	ray->x_intercept = floor(global->player->x / TILE_SIZE) * TILE_SIZE;
	if (ray->is_ray_facing_right == 1)
		ray->x_intercept += TILE_SIZE;
	ray->y_intercept = global->player->y + \
	((ray->x_intercept - global->player->x) * tan(ray_angle));
	ray->x_steps = TILE_SIZE;
	if (ray->is_ray_facing_left == 1)
		ray->x_steps *= -1;
	ray->y_steps = TILE_SIZE * tan(ray_angle);
	if (ray->is_ray_facing_up == 1 && ray->y_steps > 0)
		ray->y_steps *= -1;
	if (ray->is_ray_facing_down == 1 && ray->y_steps < 0)
		ray->y_steps *= -1;
	ray->next_vertcl_touch_x = ray->x_intercept;
	ray->next_vertcl_touch_y = ray->y_intercept;
	if (ray->is_ray_facing_left == 1)
		ray->next_vertcl_touch_x--;
	ray->distance = sqrt(pow((ray->x_intercept - global->player->x), 2) + \
	pow((ray->x_intercept - global->player->x) * tan(ray_angle), 2));
	ray->window_w = global->map->width * TILE_SIZE;
	ray->window_h = global->map->height * TILE_SIZE;
}

/**
 * It finds the closest wall in the direction of the ray
 * 
 * @param var a pointer to the struct that contains all the information about the game
 * @param ray_angle the angle of the ray we're casting
 * 
 * @return A ray struct.
 */
t_ray	vertical_intersection(t_var *var, float ray_angle)
{
	t_ray	ray;

	facing_of_ray(&ray, ray_angle, var);
	init_vertical(var, ray_angle, &ray);
	while (ray.next_vertcl_touch_x >= 0 && ray.next_vertcl_touch_x < ray.window_w
		&& ray.next_vertcl_touch_y >= 0 && ray.next_vertcl_touch_y < ray.window_h)
	{
		if (has_wall(ray.next_vertcl_touch_x, \
		ray.next_vertcl_touch_y, var, 99) == 1)
			return (ray);
		ray.next_vertcl_touch_x += ray.x_steps;
		ray.next_vertcl_touch_y += ray.y_steps;
		ray.distance += sqrt(pow(ray.x_steps, 2) + pow(ray.y_steps, 2));
	}
	ray.distance = ray.window_w * ray.window_h;
	return (ray);
}
