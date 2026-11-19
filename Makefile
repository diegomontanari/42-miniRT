NAME		= miniRT

CC			= cc
GCFLAGS 	= -Wall -Wextra -Werror
INCLUDES 	= -Iincludes -I$(LIBFT_DIR)/INC -I$(MLX_DIR)

#--LIBRARIES
LIBFT_DIR 	= libft
LIBFT 		= $(LIBFT_DIR)/libft.a
MLX_DIR 	= minilibx-linux
MLX 		= $(MLX_DIR)/libmlx.a
LIBS 		= $(LIBFT) $(MLX) -lm -lXext -lX11

#--DIRECTORIES

HEADERS 	= includes/minirt.h

SRC_DIR 	= src

SRCS 		= src/main.c \
			  src/objects/hit_cylinder.c\
			  src/parser/parse_elements.c \
			  src/parser/parse_file.c \
			  src/parser/parse_line.c \
			  src/parser/parse_objects.c \
			  src/parser/parse_utils.c \
			  src/parser/parse_values.c \
			  src/parser/read_file.c \
			  src/scene/print_scene.c \
			  src/scene/scene_utils.c \
			  src/scene/test_scene.c \
			  src/utils/ft_atof.c \
			  src/vec3/vec3_basic.c \
			  src/vec3/vec3_utils.c

TEST_SRCS 	= tests/test_cylinder.c \
			  tests/test_scene.c \
			  tests/test_vec3.c 

OBJ_DIR 	= objs
OBJS 		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#--SCENE FILE
SCENE 		= scenes/test.rt

#--TESTS
TESTS_DIR 	= tests

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(GCFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(GCFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) || test -f $(LIBFT)

$(MLX):
	@$(MAKE) -C $(MLX_DIR) || test -f $(MLX)

test: $(NAME)
	./$(NAME) $(SCENE)


clean:
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test