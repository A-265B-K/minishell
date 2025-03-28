BLACK     	= \033[30m
RED_B		= \033[41m
WHITE  		= \033[97m
RESET   	= \033[0m

NAME	= minishell
CC		= cc
CFLAGS	= -Werror -Wextra -Wall -march=native -Wunused-function -D_GNU_SOURCE -fsanitize=address
INC		= -I ./incl/
SRC_PATH	= src/
SRC 		= \
			src/clean_shell.c \
			src/env_tools.c \
			src/error.c \
			src/exe_builtins.c \
			src/exe_cd.c \
			src/exe_exit.c \
			src/exe_export.c \
			src/exe_main.c \
			src/exe_pipes.c \
			src/exe_redirects.c \
			src/exe_tools.c \
			src/exe_unset.c \
			src/export_tools.c \
			src/heredoc_tools.c \
			src/heredoc.c \
			src/lexer_group.c \
			src/lexer_tokens.c \
			src/lexer_tools.c \
			src/lexer.c \
			src/minishell.c \
			src/parse_actions.c \
			src/parse_quotes.c \
			src/parser_expand.c \
			src/parser_tools.c \
			src/parser.c \
			src/signals.c \
			src/syntax_tools.c \
			src/syntax.c \
			src/tools_two.c \
			src/tools.c

OBJ_PATH	= obj/
OBJ 		= $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))  

LIBFT_PATH	= libft/
LIBFT		= $(LIBFT_PATH)/libft.a

COMPILED    = 0

all: $(NAME)
	@if [ "$(COMPILED)" -eq 0 ]; then \
		echo "$(RED_B) $(WHITE)Nothing to be done for 'all'$(RESET)"; \
	fi
                                                                                                                                                                                           
$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@$(eval COMPILED=1)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJ_PATH) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBFT) -lreadline -lm
	@if [ $(COMPILED) -eq 1 ]; then \
		echo "$(RED_B) $(WHITE)Compiled $(NAME) $(RESET)"; \
	fi

bonus: all

clean:
	@rm -rf $(OBJ_PATH)
	@$(MAKE) $(LIBFT_PATH)
	@echo "$(RED_B) $(WHITE)Cleaned $(NAME) .o files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED_B) $(WHITE)Removed $(NAME) $(RESET)"

re: fclean all

.PHONY: all re clean fclean