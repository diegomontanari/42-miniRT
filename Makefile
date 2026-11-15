NAME		= miniRT

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iincludes
LDLIBS		= -lm

SRCS		= src/main.c \
			  src/vec3/vec3_basic.c \
			  src/vec3/vec3_utils.c \
			  src/scene/scene_utils.c \
			  src/scene/print_scene.c \
			  src/utils/str_utils.c \
			  src/utils/split.c \
			  src/utils/ft_atof.c \
			  src/parser/read_file.c \
			  src/parser/parse_file.c \
			  src/parser/parse_line.c \
			  src/parser/parse_values.c \
			  src/parser/parse_elements.c \
			  src/parser/parse_objects.c \
			  src/objects/hit_cylinder.c

OBJ_DIR		= obj
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Objects shared by the test programs (everything except main.c)
LIB_OBJS	= $(filter-out $(OBJ_DIR)/src/main.o, $(OBJS))
TEST_SCENE	= $(OBJ_DIR)/src/scene/test_scene.o
TESTS		= test_vec3 test_scene test_cylinder

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c includes/minirt.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Test programs, not part of the evaluated project: make tests
tests: $(TESTS)

test_vec3: tests/test_vec3.c $(LIB_OBJS)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

test_scene: tests/test_scene.c $(TEST_SCENE) $(LIB_OBJS)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

test_cylinder: tests/test_cylinder.c $(LIB_OBJS)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(TESTS)

re: fclean all

.PHONY: all clean fclean re tests
