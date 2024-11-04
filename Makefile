BLACK     	= \033[30m
RED_B		= \033[41m
WHITE  		= \033[97m
RESET   	= \033[0m

NAME	= minishell
CC		= cc
CFLAGS	= -Werror -Wextra -Wall -Wunreachable-code -march=native -g
INC		= -I ./incl/
SRC_PATH	= src/
SRC 		= $(wildcard $(SRC_PATH)*/*.c) $(wildcard $(SRC_PATH)/*.c)

OBJ_PATH	= obj/
OBJ 		= $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))  

LIBFT_PATH	= libft/
LIBFT		= $(LIBFT_PATH)build/libft.a

COMPILED    = 0

all: $(NAME)
	@if [ "$(COMPILED)" -eq 0 ]; then \
		echo "$(RED_B) $(WHITE)Nothing to be done for 'all'$(RESET)"; \
	fi
                                                                                                                                                                                           
$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@$(eval COMPILED=1)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJ_PATH) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBFT) -lreadline -lXext -lX11 -lm
	@if [ $(COMPILED) -eq 1 ]; then \
		echo "$(RED_B) $(WHITE)Compiled $(NAME) $(RESET)"; \
	fi

bonus: all

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(RED_B) $(WHITE)Cleaned $(NAME) .o files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED_B) $(WHITE)Removed $(NAME) $(RESET)"

re: fclean all

.PHONY: all re clean fclean
