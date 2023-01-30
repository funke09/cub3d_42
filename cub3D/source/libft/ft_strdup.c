/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:01:18 by zcherrad          #+#    #+#             */
/*   Updated: 2023/01/30 22:30:55 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*ns1;
	int		i;

	if(!s1)
		return (NULL);
	len = ft_strlen(s1);
	ns1 = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ns1)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ns1[i] = s1[i];
		i++;
	}
	return (ns1);
}
