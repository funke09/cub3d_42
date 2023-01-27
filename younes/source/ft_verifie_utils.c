/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verifie_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammam <ahammam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:55:10 by ahammam           #+#    #+#             */
/*   Updated: 2022/11/19 19:35:13 by ahammam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1 && s2 && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i++;
    return (s1[i] - s2[i]);
}

void ft_free_split(char **tab)
{
    int i;

    i = 0;
    while (tab && tab[i])
    {
        free(tab[i]);
        i++;
    }
    if (tab)
        free(tab);
}

int ft_is_exist(char *str, char c)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int ft_len_split(char **tab)
{
    int i;

    i = 0;
    while (tab && tab[i])
        i++;
    return (i);
}