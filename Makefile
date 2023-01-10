NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
# MLX = libmlx.dylib
MLXFLAGS =  -lmlx -framework OpenGL -framework AppKit -lm
SRCS = cub.c main.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)
	$(CC) $(CFLAGS)  -o $(NAME) $(OBJS) $(LIBFT) $(MLXFLAGS)

$(NAME) : $(OBJS)
	make -C libft
	# make -C $(MLX)

clean :
	rm -f $(OBJS)
	make clean -C libft
	# make clean -C $(MLX)


fclean : clean
	rm -f $(NAME)
	make fclean -C libft
	# make clean -C $(MLX)

re : fclean all

	