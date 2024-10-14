CC				= cc
AR				= ar rc
CFLAGS			= -Wall -Wextra -Werror
NAME			= ./build/libft.a
RM				= rm -rf
SRC_DIR			= src
BUILD_DIR		= build
SRC				=	ft_atoi.c               ft_isprint.c       ft_memcpy.c       ft_strjoin.c \
					ft_atol.c 				ft_alloc.c			ft_abs.c \
					ft_bzero.c              ft_isspace.c       ft_memmove.c      ft_strlcat.c \
					ft_calloc.c             ft_istab.c         ft_memset.c       ft_strlcpy.c \
					ft_count_words.c        ft_iswhitespace.c  ft_printf.c       ft_strlen.c  \
					ft_free_and_null.c      ft_itoa.c          ft_put_address.c  ft_strmapi.c \
					ft_free_strs.c    ft_lstadd_back.c   ft_putchar_fd.c   ft_strncmp.c \
					ft_free_n_strs.c  ft_lstadd_front.c  ft_putendl_fd.c   ft_strndup.c \
					ft_get_hex_value.c      ft_lstclear.c      ft_puthex.c       ft_strnstr.c \
					ft_hex_len.c            ft_lstdelone.c     ft_putnbr_fd.c    ft_strrchr.c \
					ft_hex_to_uint.c        ft_lstiter.c       ft_putstr_fd.c    ft_strtrim.c \
					ft_isalnum.c            ft_lstlast.c       ft_put_unum.c     ft_substr.c  \
					ft_isalpha.c            ft_lstmap.c        ft_split.c        ft_tolower.c \
					ft_isascii.c            ft_lstnew.c        ft_strchr.c       ft_toupper.c \
					ft_isdigit.c            ft_lstsize.c       ft_strcmp.c       get_next_line.c \
					ft_ishex.c              ft_memchr.c        ft_strdup.c       get_next_line_utils.c \
					ft_isnl.c               ft_memcmp.c        ft_striteri.c     ft_array_len.c \

SRC_FILES		= $(addprefix $(SRC_DIR)/, $(SRC))
OBJECT_FILES	= $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECT_FILES)
	@mkdir -p $(@D)
	@ar rcs $@ $^
	@printf "$(GREEN)Built libft\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(GREEN)Cleaning..."
	@$(RM) $(OBJECT_FILES)
	@printf "$(GREEN) done!\n"

fclean:
	@printf "$(GREEN)Fcleaning..."
	@$(RM) $(BUILD_DIR)
	@printf "$(GREEN) done!\n"

re:
	@make -s fclean
	@make -s all

.PHONY: clean fclean re

GREEN	:= \033[32;1m
