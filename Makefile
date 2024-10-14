NAME			= minishell
CFLAGS			= -Wextra -Wall -Werror -Wunreachable-code -g
LIBFT			= ./libft
BUILD_DIR		= ./build
SRC_DIR			= ./src
HEADERS			= -I ./inc -I $(LIBFT)/inc
LIBS			= $(LIBFT)/build/libft.a
SOURCE_FILES	= $(wildcard $(SRC_DIR)/*.c)
OBJECT_FILES	= $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCE_FILES))

all: libft $(NAME)

libft:
	make -C $(LIBFT)

$(NAME): $(OBJECT_FILES)
	@$(CC) $(OBJECT_FILES) $(LIBS) $(HEADERS) -lreadline -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

clean:
	@rm -rf $(OBJECT_FILES)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

run: all
	./$(NAME)

rerun: all fclean
	make fclean
	make run

.PHONY: all clean fclean re run libft
