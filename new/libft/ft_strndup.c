/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 05:54:25 by zcherrad          #+#    #+#             */
/*   Updated: 2022/05/18 05:55:56 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	int		len;
	char	*ns1;
	int		i;

	len = ft_strlen(s1);
	ns1 = (char *)ft_calloc(len + 1, sizeof(char));
	if (ns1 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && n--)
	{
		ns1[i] = s1[i];
		i++;
	}
	return (ns1);
}
