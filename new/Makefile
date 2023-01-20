NAME = cub3d
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address 
HEADER = cub3d.h
LIBFT = libft/libft.a
MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
SRCS = main.c tolls_map.c tools_map.c read_map.c init_t_map.c check_map.c init_game.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) $^ $(LIBFT) $(MLXFLAGS) -o $@

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@make clean -C libft
	rm -f $(OBJS)


fclean : clean
	make fclean -C libft
	rm -f $(NAME)

re : fclean all
