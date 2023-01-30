/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 06:09:30 by zcherrad          #+#    #+#             */
/*   Updated: 2023/01/14 23:42:24 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<stdlib.h>
# include<unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 25
# endif

char	*ft_strchr2(char *s, int c);

size_t	ft_strlen2(char *str);

char	*get_all_line(int fd, char *str);

char	*get_line(char *str);

char	*get_next_line(int fd);

char	*ft_strjoin(char *str, char *buff);

char	*get_rest(char *str);
#endif
