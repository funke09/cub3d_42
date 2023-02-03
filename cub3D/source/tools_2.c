/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:17:40 by zcherrad          #+#    #+#             */
/*   Updated: 2023/02/03 02:56:01 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * It checks if the string is a parameter
 * 
 * @param str the string to check
 * 
 * @return 1 if the string is a parameter, 0 if not.
 */
int	is_param(char *str)
{
	if (!ft_strcmp(str, "NO") || !ft_strcmp(str, "SO")
		|| !ft_strcmp(str, "WE") || !ft_strcmp(str, "EA")
		|| !ft_strcmp(str, "F") || !ft_strcmp(str, "C"))
		return (1);
	return (0);
}

/**
 * It returns a number that represents the parameter
 * 
 * @param str the string to check
 * 
 * @return the number of the parameter.
 */
int	param_number(char *str)
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

/**
 * It checks if the string is a valid color
 * 
 * @param str The string to be checked.
 * 
 * @return the value of the variable i.
 */
int	valid_color(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == ',')
		{
			if (str[i] == ',' && (str[i + 1] == ',' || str[i + 1] == '\0'))
				return (0);
			i++;
		}
		else
			return (0);
	}
	return (1);
}

/**
 * It takes an angle in radians and 
 * returns the equivalent angle between 0 and 2*pi
 * 
 * @param angle The angle to normalize.
 * 
 * @return The angle in radians.
 */
float	normalize(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = angle + (2 * M_PI);
	return (angle);
}

/**
 * It takes a string and a length, and returns 
 * a string of the same length, with the first non-null
 * character of the original string, and all 
 * subsequent characters replaced with spaces
 * 
 * @param s1 the string to be copied
 * @param len the length of the string to be duplicated
 * 
 * @return A pointer to a string.
 */
char	*dup_cub(char *s1, int len)
{
	int		i;
	char	*dst;
	int		flag;

	i = 0;
	flag = 0;
	dst = malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	while (i < len)
	{
		if (flag == 0 && s1[i] != '\0' && s1[i] != '\n')
			dst[i] = s1[i];
		else
			flag = 1;
		if (flag == 1)
			dst[i] = ' ';
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
