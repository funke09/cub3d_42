
#include "cub3D.h"

/**
 * It takes in four integers,
 * each representing a color component, and returns a string representing the
 * color in hexadecimal format
 * 
 * @param t transparency
 * @param r red
 * @param g green
 * @param b blue
 * 
 * @return A string of the hexadecimal value of the color.
 */
char	*from_rgb_tohex(int t, int r, int g, int b)
{
	char	*color_hex;
	char	*base;

	if (r < 0 || g < 0 || b < 0 || t < 0
		|| r > 255 || g > 255 || b > 255 || t > 255)
		return (NULL);
	color_hex = (char *) malloc(sizeof(char) * 9);
	if (!color_hex)
		return (NULL);
	base = "0123456789abcdef";
	color_hex[0] = base[t / 16];
	color_hex[1] = base[t % 16];
	color_hex[2] = base[r / 16];
	color_hex[3] = base[r % 16];
	color_hex[4] = base[g / 16];
	color_hex[5] = base[g % 16];
	color_hex[6] = base[b / 16];
	color_hex[7] = base[b % 16];
	color_hex[8] = '\0';
	return (color_hex);
}

/**
 * It converts a hexadecimal number to a decimal number
 * 
 * @param number The hexadecimal number to be converted.
 * 
 * @return the decimal value of the hexadecimal number.
 */
unsigned int	hex_to_dec(char *number)
{
	unsigned int	intgr;
	int				decimal;
	int				i;

	i = -1;
	intgr = 0;
	while (number[++i])
	{
		if (number[i] == 'a')
			decimal = 10;
		else if (number[i] == 'b')
			decimal = 11;
		else if (number[i] == 'c')
			decimal = 12;
		else if (number[i] == 'd')
			decimal = 13;
		else if (number[i] == 'e')
			decimal = 14;
		else if (number[i] == 'f')
			decimal = 15;
		else
			decimal = number[i] - 48;
		intgr = intgr * 16 + decimal;
	}
	return (intgr);
}


/**
 * It converts a color from RGB to decimal
 * 
 * @param t transparency (0-255)
 * @param r red
 * @param g green
 * @param b blue
 * 
 * @return the decimal value of the hexadecimal value of the rgb value.
 */
unsigned int	convert_rgb_dec(int t, int r, int g, int b)
{
	char	*rgb_to_h;
	int		hex_to_d;

	rgb_to_h = from_rgb_tohex(t, r, g, b);
	hex_to_d = hex_to_dec(rgb_to_h);
	free(rgb_to_h);
	return (hex_to_d);
}


/**
 * It takes a string, splits it into an array of strings, and returns the value of the string at the
 * index specified by the second parameter
 * 
 * @param color the color of the object
 * @param rgb 1 = red, 2 = green, 3 = blue
 * 
 * @return The color of the object.
 */
int	check_color(char *color, int rgb)
{
	char	**new;
	int		new_color;
	int		i;

	new = ft_split(color, ',');
	new_color = 0;
	if(!new[0] || !new[1] || !new[2])
	{
			printf("Error\nmissing parameter color\n");
			exit(0);
	}
	if (!new)
		return (0);
	if (rgb == 1)
		new_color = ft_atoi(new[0]);
	else if (rgb == 2)
		new_color = ft_atoi(new[1]);
	else if (rgb == 3)
		new_color = ft_atoi(new[2]);
	i = -1;
	while (new[++i])
		free(new[i]);
	free(new);
	return (new_color);
}
