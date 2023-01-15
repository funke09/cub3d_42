/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 06:10:36 by zcherrad          #+#    #+#             */
/*   Updated: 2023/01/14 23:42:33 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_all_line(int fd, char *str)
{
	int		byte;
	char	*buff;

	byte = 1;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (byte != 0)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[byte] = '\0';
		str = ft_strjoin(str, buff);
		if (ft_strchr2(str, '\n'))
			break ;
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*dest;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = get_all_line(fd, str);
	if (!str)
		return (NULL);
	dest = get_line(str);
	str = get_rest(str);
	return (dest);
}