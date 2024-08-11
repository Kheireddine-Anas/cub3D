
SRCS =	main.c getNextLine/get_next_line_utils_bonus.c getNextLine/get_next_line_bonus.c parssing/spliter.c parssing/utils.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -I.
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
MLX				= libmlx.dylib
NAME			= cub3D
LIBFT 			= libft/libft.a
all:			$(NAME)

$(NAME):		$(MLX) $(OBJS)
				@$(MAKE) -C libft 
				gcc ${CFLAGS} -o ${NAME} libft/libft.a	${OBJS} ${LIBS}

$(MLX):
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) 

clean:
				@$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re