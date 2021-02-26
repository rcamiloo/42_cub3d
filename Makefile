NAME = 		cub3D
SRCS_DIR = 	srcs
OBJS_DIR =	.objs
FT_DIR = 	libft
FT = 		$(FT_DIR)/libft.a
SRCS = 		$(SRCS_DIR)/scene.c

OBJS = 		$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

CC = 		clang
HEAD = 		-I./include -I./$(FT_DIR)

LFLAGS = 	-L ./$(FT_DIR) -lft
RM = 		/bin/rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(FT)
		$(CC) $(OBJS) $(HEAD) $(LFLAGS) -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		mkdir -p $(OBJS_DIR)
		$(CC) $(HEAD) -c $< -o $@

$(FT):
		make -C $(FT_DIR)

debug: $(OBJS) $(FT)
		$(CC) -g $(OBJS) $(HEAD) $(LFLAGS) -o cub3D_debug
		mv cub3D_debug ./srcs
clean:
		make clean -C $(FT_DIR)
		$(RM) $(OBJS_DIR)

fclean: clean
		$(RM) $(NAME)
		$(RM) *.bmp
re: fclean all

.PONY:all clean fclean re

