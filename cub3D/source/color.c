
#include "cub3D.h"

// this function convert trgb to hexcolor
char	*ft_trgb_to_hex(int t, int r, int g, int b)
{
	char	*base;
	char	*hex;

	if (r < 0 || g < 0 || b < 0 || t < 0
		|| r > 255 || g > 255 || b > 255 || t > 255)
		return (NULL);
	hex = (char *) malloc(sizeof(char) * 9);
	if (!hex)
		return (NULL);
	base = "0123456789abcdef";
	hex[0] = base[t / 16];
	hex[1] = base[t % 16];
	hex[2] = base[r / 16];
	hex[3] = base[r % 16];
	hex[4] = base[g / 16];
	hex[5] = base[g % 16];
	hex[6] = base[b / 16];
	hex[7] = base[b % 16];
	hex[8] = '\0';
	return (hex);
}

// this function convert hexcolor to decimal 
unsigned int	ft_hexcolor_to_decimal(char *hex)
{
	int				i;
	int				dec;
	unsigned int	decimal;

	i = -1;
	decimal = 0;
	while (hex[++i])
	{
		if (hex[i] == 'a')
			dec = 10;
		else if (hex[i] == 'b')
			dec = 11;
		else if (hex[i] == 'c')
			dec = 12;
		else if (hex[i] == 'd')
			dec = 13;
		else if (hex[i] == 'e')
			dec = 14;
		else if (hex[i] == 'f')
			dec = 15;
		else
			dec = hex[i] - 48;
		decimal = decimal * 16 + dec;
	}
	return (decimal);
}

// this function convert trgb to decimal
unsigned int	convert_rgb_dec(int t, int r, int g, int b)
{
	char	*trgb_to_hex;
	int		hex_to_int;

	trgb_to_hex = ft_trgb_to_hex(t, r, g, b);
	hex_to_int = ft_hexcolor_to_decimal(trgb_to_hex);
	free(trgb_to_hex);
	return (hex_to_int);
}

// this function will return the int value of:
//  'r' if rgb = 1 or 'g' if rgb = 2 or 'b' if rgb = 3
int	check_color(char *color, int rgb)
{
	char	**s_rgb;
	int		rgb_value;
	int		i;

	s_rgb = ft_split(color, ',');
	//printf("size = %d\nrgb = %d\n", i, rgb);
	rgb_value = 0;
	if(!s_rgb[0] || !s_rgb[1] || !s_rgb[2])
	{
			printf("Error\nInvalid color\n");
			exit(0);
	}
	if (!s_rgb)
		return (0);
	if (rgb == 1)
		rgb_value = ft_atoi(s_rgb[0]);
	else if (rgb == 2)
		rgb_value = ft_atoi(s_rgb[1]);
	else if (rgb == 3)
		rgb_value = ft_atoi(s_rgb[2]);
	i = -1;
	while (s_rgb[++i])
		free(s_rgb[i]);
	free(s_rgb);
	return (rgb_value);
}
