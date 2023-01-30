
NAME = cub3D
BONUS = cub3D_bonus

# madatory
SRC_FOLDER = ./source/
SRC = main.c error.c map.c map_check.c ft_verifie_utils.c ft_verifie.c fill_data.c draw.c player.c rays.c render.c wall_intersections.c color.c handler.c ft_verifie_utils2.c
SRCS = $(addprefix $(SRC_FOLDER), $(SRC))
SRCOBJ = ${SRCS:.c=.o}


LIBFT_FOLDER = ./source/libft/
LIBFT_FILES =	ft_isdigit.c ft_memset.c ft_strjoin.c ft_strtrim.c ft_isprint.c\
					ft_putchar_fd.c ft_strlcat.c ft_substr.c ft_itoa.c ft_atoi.c ft_putendl_fd.c\
					ft_strlcpy.c ft_tolower.c ft_bzero.c  ft_putnbr_fd.c ft_strlen.c\
					ft_toupper.c ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_isalnum.c\
					ft_memcmp.c ft_split.c ft_strncmp.c ft_isalpha.c ft_memcpy.c ft_strchr.c\
					ft_strnstr.c ft_isascii.c ft_memmove.c ft_strdup.c ft_strrchr.c ft_striteri.c get_next_line.c get_next_line_utils.c
SRCS_LIBFT = $(addprefix $(LIBFT_FOLDER), $(LIBFT_FILES))

OTHER_SRCS = $(SRCS_FT_PRINTF) $(SRCS_GET_NEXT_LINE) $(SRCS_LIBFT)
OTHER_OBJ = ${OTHER_SRCS:.c=.o}

LIBS =  ./source/libft/libft.a

INCLUDES = ./source/cub3D.h ./source/libft/libft.h 

# -g for the debugger
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CC = cc 

%.o : %.c ${INCLUDES}
	$(CC) ${FLAGS} -Imlx -c $< -o $@
	
$(NAME) : ${SRCOBJ} $(OTHER_SRCS)
	@$(MAKE) -C $(LIBFT_FOLDER)
	@$(CC) ${FLAGS} $(SRCOBJ) $(LIBS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "|+| make the get_next_line.a [${GREEN}DONE${RESET}]"
	@echo "|+| make the libft.a         [${GREEN}DONE${RESET}]"
	@echo "|+| make the $(NAME) program   [${GREEN}DONE${RESET}]"
	clear

# @$(CC) ${FLAGS} $(SRCOBJ) $(LIBS) -o $(NAME)

bonus:
	@echo "did not make it yet!"

all : $(NAME)  

clean :
	@rm -f $(LIBS) $(OTHER_OBJ) $(SRCOBJ) $(SRCOBJ_B)
	@echo "|-| remove object files [${RED}DONE${RESET}]"

fclean : clean
	@rm -f ${NAME}
	@echo "|-| remove the program  [${RED}DONE${RESET}]"

re : fclean all




# colors used
GREEN = \033[0;92m
RED = \033[0;91m
RESET = \033[0m