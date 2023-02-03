/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:18:43 by zcherrad          #+#    #+#             */
/*   Updated: 2023/02/03 14:27:31 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * It compares two strings and returns the
 * difference between the first two characters that are
 * different
 * 
 * @param s1 The first string to be compared.
 * @param s2 The string to compare to s1.
 * 
 * @return The difference between the first two characters
 * that differ in the strings s1 and s2.
 */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

/**
 * It frees a 2D array
 * 
 * @param tab The array of strings to be freed.
 */
void	free_loop(char **tab)
{
	int		i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

/**
 * It counts the number of elements in a 2D array
 * 
 * @param tab The array of strings to be counted.
 * 
 * @return The number of elements in the array.
 */
int	count_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}
