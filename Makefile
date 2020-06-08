NAME = bmp_reader
FLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c srcs/utilities.c
LIBS = minilibx_macos/libmlx.a libft/libft.a
FRAMEWORK = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	@echo "compiling..."
	@gcc -o $(NAME) $(SRCS) $(LIBS) $(FRAMEWORK)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all
