SRCS =	main.c getNextLine/get_next_line_utils.c getNextLine/get_next_line.c parsing/util1_chek_and_initialis.c parsing/util2_map_initailis.c texture/draw.c texture/control_kebord.c\
		texture/draw_util1.c  texture/ray.c texture/rander_util1.c  texture/rander_wall.c  texture/chek_distance_horizental.c  texture/draw_mini_map.c texture/chek_distance_vertical.c texture/door.c texture/control_kebord_util1.c\
		texture/control_kebord_util2.c

OBJS			= $(SRCS:.c=.o)

CC			= cc
RM			= rm -f
CFLAGS		=  -Wall -Wextra -Werror   
# -fsanitize=address
MLX_LIB	=   MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/ahamdi/.brew/opt/glfw/lib/"
NAME		= cub3D
LIBFT 		= libft/libft.a

all:		$(NAME)

$(NAME):	$(OBJS)
			make -C libft 
			$(CC) ${CFLAGS} -o ${NAME} ${LIBFT} ${OBJS} ${MLX_LIB}

%.o:	%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			make -C libft clean
			$(RM) $(OBJS)

fclean:		clean
			make -C libft fclean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re