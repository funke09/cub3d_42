# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 02:18:15 by zcherrad          #+#    #+#              #
#    Updated: 2023/01/31 02:27:53 by zcherrad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS =ft_atoi.c\
ft_bzero.c\
ft_calloc.c\
ft_isalnum.c\
ft_isalpha.c\
ft_isdigit.c\
ft_putchar_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_putstr_fd.c\
ft_split.c\
ft_strchr.c\
ft_strdup.c\
ft_strjoin.c\
ft_strlen.c\
get_next_line_utils.c\
get_next_line.c\



OBJS = $(SRCS:.c=.o)
CFLAGS = -g -Wall -Werror -Wextra
CC = gcc
RM = rm -f
AR = ar rc

all: $(NAME)

$(NAME):$(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

# bonus:$(B_OBJS) $(OBJS)
# 	$(AR) $(NAME) $(B_OBJS) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean:clean
	$(RM) $(NAME)

re: fclean all