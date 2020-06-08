# NAME = bmp_reader
# FLAGS = -Wall -Wextra -Werror
# SRCS = srcs/main.c srcs/utilities.c
# LIBS = minilibx_macos/libmlx.a libft/libft.a
# FRAMEWORK = -framework OpenGL -framework AppKit

# all: $(NAME)

# $(NAME):
# 	@echo "compiling..."
# 	@gcc -o $(NAME) $(SRCS) $(LIBS) $(FRAMEWORK)

# clean:
# 	@rm -f *.o

# fclean: clean
# 	@rm -f $(NAME)

# re: fclean all

NAME = lib_bmp.a
CFILES = read utilities
OFILES = $(CFILES:%=.objects/%.o)

all: $(NAME)

$(NAME): $(OFILES)
	@ar rc $(NAME) $^
	@echo "compiled successfully!"

.objects/%.o: srcs/%.c srcs/bmp.h
	@mkdir -p .objects
	@$(CC) -o $@ -c $<

clean:
	rm -rf .objects

fclean: clean
	rm -f $(NAME)

re: fclean all 
