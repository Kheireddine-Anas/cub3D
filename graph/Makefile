NAME = cub3D

SRC =	graph.c

CFLAGS = -Wall -Wextra -Werror -IMLX42

OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) -lglfw -framework Cocoa -framework OpenGL -framework IOKit MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/akheired/.brew/opt/glfw/lib/" -o $(NAME)

clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all