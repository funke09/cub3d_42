
#include "cub3D.h"

int	ft_is_flag(char *str)
{
	if (!ft_strcmp(str, "NO") || !ft_strcmp(str, "SO")
		|| !ft_strcmp(str, "WE") || !ft_strcmp(str, "EA")
		|| !ft_strcmp(str, "F") || !ft_strcmp(str, "C"))
		return (1);
	return (0);
}

int	ft_nbr_flag(char *str)
{
	if (!ft_strcmp(str, "SO"))
		return (1);
	else if (!ft_strcmp(str, "WE"))
		return (10);
	else if (!ft_strcmp(str, "EA"))
		return (100);
	else if (!ft_strcmp(str, "NO"))
		return (1000);
	else if (!ft_strcmp(str, "F"))
		return (10000);
	else if (!ft_strcmp(str, "C"))
		return (100000);
	return (0);
}

int	ft_is_gbr_valid(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == ',')
		{
			if (str[i] == ',' && str[i + 1] == ',')
				return (0);
			i++;
		}
		else
			return (0);
	}
	return (1);
}

// this function limits the angle between (0~360) degree or (0~2PI) radian
float	ft_normalize_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = angle + (2 * M_PI);
	return (angle);
}
