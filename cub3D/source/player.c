
#include "cub3D.h"

// this function get the player.rotation_angle
// based on the player orientation player_derection
float	check_angle(char c)
{
	if (c == 'W')
		return (M_PI);
	else if (c == 'E')
		return (0);
	else if (c == 'N')
		return ((3 * M_PI) / 2);
	else if (c == 'S')
		return (M_PI / 2);
	return (0);
}

float ft_normalize_promax(int isfront, t_player *p)
{
	float	angle;

	if (isfront == 1)
		angle = normalize(p->rotate_angle);
	else if (isfront == -1)
		angle = normalize(p->rotate_angle - (M_PI / 2));
	else if (isfront == -2)
		angle = normalize(p->rotate_angle + (M_PI / 2));
	else 
		angle = normalize(p->rotate_angle + M_PI);
	return (normalize(angle));
}


int	ft_special_case(int x, int y, t_var *var, int isfront)
{
	t_player *p;
	t_map *map;
	float angle;
	
	p = var->player;
	map = var->map;
	angle = ft_normalize_promax(isfront, p);
	if (angle >= 0 && (angle < M_PI / 2))
		if ( map->map[y + 1][x] == '1' && map->map[y][x + 1] == '1')
			return (1);
	if (angle >= (M_PI/2) && (angle <= (M_PI)))
		if ( map->map[y + 1][x] == '1' && map->map[y][x - 1] == '1')
			return (1);
	if (angle >= (M_PI) && (angle < (3 * M_PI / 2)))
		if ( map->map[y - 1][x] == '1' && map->map[y][x - 1] == '1')
			return (1);
	if (angle >= (3 * M_PI / 2) && (angle <= 2 * M_PI))
		if ( map->map[y - 1][x] == '1' && map->map[y][x + 1] == '1')
			return (1);
	return (0);
}

// this function draw the player on the map
void	player_rendr(t_var *var)
{
	int	y;
	int	x;
	int	sizeofplayer;
	int	i;

	y = var->player->minimap_size / 2;
	x = var->player->minimap_size / 2;
	i = -1;
	sizeofplayer = var->player->sizeofplayer;
	draw_square(y, x, sizeofplayer, var);
}

// this function checks if there is a wall in the position map[new_y][new_x]
int	has_wall(int new_x, int new_y, t_var *var, int front)
{
	int	w;
	int	h;

	w = (var->map->width) * TILE_SIZE;
	h = (var->map->height) * TILE_SIZE;
	if (new_x < 0 || new_x > w || new_y < 0 || new_y > h)
		return (1);
	if (var->map->map[new_y / TILE_SIZE][new_x / TILE_SIZE] != '0')
		return (1);
	if (var->map->map[new_y / TILE_SIZE][new_x / TILE_SIZE] != '0')
		return (1);
	if (ft_special_case(var->player->x / TILE_SIZE, var->player->y / TILE_SIZE, var, front) == 1)
		return (1);
	else
		return (0);
}


void move_left(t_player *player, float fixedangle, float *new_x, float *new_y)
{
	*new_x = player->x + player->move_speed * cos(fixedangle);
	*new_y = player->y + player->move_speed * sin(fixedangle);
}

void	update(t_var *var, int key)
{
	float		move_step;
	float		new_x;
	float		new_y;
	t_player	*player;

	player = var->player;
	move_step = player->move_speed;
	// if (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_D
	// 	|| key == KEY_A )
	// {
		if( key == KEY_A)
		{
			//move_left(player, player->rotate_angle - (M_PI / 2), &new_x, &new_y);
			new_x = player->x + move_step * cos(player->rotate_angle - (M_PI / 2));
			new_y = player->y + move_step * sin(player->rotate_angle - (M_PI / 2));
		}
		 if ( key == KEY_D)
		{
			new_x = player->x + move_step * cos(player->rotate_angle + (M_PI / 2));
			new_y = player->y + move_step * sin(player->rotate_angle + (M_PI / 2));
		}
		if (key == KEY_A && has_wall(new_x, new_y, var, -1) == 0 )
		{	player->x = new_x;
			player->y = new_y;
		}
		 if(key == KEY_D && has_wall(new_x, new_y, var, -2) == 0)
		{
			player->x = new_x;
			player->y = new_y;
		}
		if ( key == KEY_RIGHT || key == KEY_LEFT)
		{
			player->rotate_angle =normalize(player->rotate_angle + player->turn_direction * player->rotation_speed);
			printf("rotate angle %f", player->rotate_angle);
			player->turn_direction = 0;
		}
	//}
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		move_step = player->move_speed * player->walk_direction;
		new_x = player->x + move_step * cos(player->rotate_angle);
		new_y = player->y + move_step * sin(player->rotate_angle);
		if (key == KEY_W && has_wall(new_x, new_y, var, 1) == 0  )
		{
			player->x = new_x;
			player->y = new_y;
		}
		else if ( key == KEY_S && has_wall(new_x, new_y, var, 0) == 0)
		{
			player->x = new_x;
			player->y = new_y;
		}
		

	}
	var->map->map[(int)player->y/TILE_SIZE][(int)player->x/TILE_SIZE]  = '0';
}
