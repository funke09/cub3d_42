NAME = cub3d
CC = gcc
CFLAGS =-fsanitize=address 
# -Wall -Wextra -Werror
LIBFT = libft/libft.a
MLXFLAGS =   -framework OpenGL -framework AppKit -lm
SRCS = main.c
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
