# Program Name(s)
NAME		=	minishell

# Set build directories
BUILDDIR	= build
TARGET		= bin/$(NAME)

# Compiler Settings
CC 				:= gcc
CFLAGS			+= -Werror -Wall -Wextra
CFLAGS			+= -g
CFLAGS			+= -O3

# # Debug mode by default for now
CFLAGS += -g -fsanitize=address

# Libraries
LIBDIR			=	lib

LIBS			=	libft


MOD_READLINE	=	readline
EXTRA_LIBS		=  -lncurses

MOD_LIBFT		=	libft

MODS			=	$(MOD_LIBFT)

LIBARIES_AFILES	=	${addprefix $(BUILDDIR)/, ${addsuffix .a, $(LIBS)}}

# Sources
SRCDIR		= 	src
FILES		= 	minishell.c				\
				tools/error.c			\
				tools/mem.c				\
				tools/debug.c			\
				buildins/buildins.c		\
				buildins/env/env.c		\
				buildins/echo/echo.c	\
				buildins/exit/exit.c	\
				buildins/export/export.c\
				buildins/export/export_add.c\
				buildins/unset/unset.c	\
				execute/where.c			\
				execute/execute.c		\
				expander/expander.c		\
				history/history.c		\
				tokenizer/operators.c	\
				tokenizer/parameters.c	\
				tokenizer/quotes.c		\
				tokenizer/tokenizer.c	\
				tokenizer/words.c		\
				parser/parser.c			\
				parser/pipes.c			\
				parser/tasks.c			\
				env/env.c				\
				file/file.c				\
				signals/signals.c		\
				buildins/cd/cd.c		\
				tools/array.c
# input/lexer.c			\
# input/input.c			\
# input/split.c			\
# input/list.c			\
	
SOURCES		=	${addprefix $(SRCDIR)/, $(FILES)}

# Objects
OBJECTS		= $(SOURCES:%.c=$(BUILDDIR)/%.o)

# Colors
ifneq (,$(findstring xterm,${TERM}))
	BLACK		:= $(shell tput -Txterm setaf 0)
	RED			:= $(shell tput -Txterm setaf 1)
	GREEN		:= $(shell tput -Txterm setaf 2)
	YELLOW		:= $(shell tput -Txterm setaf 3)
	LIGHTPURPLE	:= $(shell tput -Txterm setaf 4)
	PURPLE		:= $(shell tput -Txterm setaf 5)
	BLUE		:= $(shell tput -Txterm setaf 6)
	WHITE		:= $(shell tput -Txterm setaf 7)
	RESET		:= $(shell tput -Txterm sgr0)
endif
	RETURN		:= "\033[0K\n"
P				:= printf "%-25.25s%s\n"
P_OK			= $(P) "$@${GREEN}" "Norm OK" "${RESET}"
P_KO			= $(P) "$@${RED}" "Norm KO" "${RESET}"

# Rules
all: $(NAME)

$(BUILDDIR)/%.o:%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@norminette -R CheckForbiddenSourceHeader $< > /dev/null 					\
		&& $(P) "Build${GREEN}" "$(notdir $<)${RESET}" 							\
		|| $(P) "Build${RED}" "$(notdir $<)${RESET}"

$(MOD_READLINE):
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/$@
	@git submodule update --init 2>&1 											\
		&& $(P) "Submodule${GREEN}" "$@$(RESET)"								\
		|| $(P) "Submodule${RED}" "$@$(RESET)"
	@[ -f $(LIBDIR)/$@/configure ]												\
		&& [ -f $(BUILDDIR)/$@/libreadline.a ] && break							\
		|| (cd $(BUILDDIR)/$@ && ../../$(LIBDIR)/$@/configure 2>&1 > /dev/null	\
			&& $(P) "$@$(GREEN)" "OK$(RESET)"									\
			|| $(P) "$@$(RED)" "Error$(RESET)")									\
		|| break
	@[ -f $(BUILDDIR)/$@/Makefile ]												\
		&& (make static -C $(BUILDDIR)/$@ > /dev/null							\
			&& $(P) "$@$(GREEN)" "OK$(RESET)"									\
			|| $(P) "$@$(RED)" "Error$(RESET)")									\
		|| break
	@[ -f $(BUILDDIR)/$@/libreadline.a ]										\
		&& cp -p $(BUILDDIR)/$@/*.a $(BUILDDIR)

$(MOD_LIBFT):
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/$@
	@git submodule update --init 2>&1 											\
		&& $(P) "Submodule${GREEN}" "$@$(RESET)"								\
		|| $(P) "Submodule${RED}" "$@$(RESET)"
	@[ -f $(LIBDIR)/$@/Makefile ]												\
		&& (make -C $(LIBDIR)/$@ > /dev/null									\
			&& $(P) "$@$(GREEN)" "OK$(RESET)"									\
			|| $(P) "$@$(RED)" "Error$(RESET)")									\
		|| break
	@[ -f $(LIBDIR)/$@/libft.a ]												\
		&& cp -p $(LIBDIR)/$@/*.a $(BUILDDIR)									\

$(NAME): $(MODS) $(OBJECTS)
	@if [ ! -d $(dir $(TARGET)) ]; then mkdir $(dir $(TARGET)); fi
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBARIES_AFILES) -o $(TARGET) 	\
		&& ($(P) "Executable $(GREEN)" "$(NAME) Created $(RESET)" && exit 0)						\
		|| ($(P) "Executable $(RED)" "$(NAME) Compile error $(RESET)" && exit 1)
	@$(P) "Flags $(YELLOW)" "$(CFLAGS) $(RESET)"
	@norminette -R CheckForbiddenSourceHeader $(SOURCES) include 2>&1 > /dev/null && ($(P) "Norminette$(GREEN)" "OK$(RESET)" && printf "\n🙏 $(GREEN)Complete $(RESET)\n") || $(P) "Norminette$(RED)" "KO$(RESET)"

clean:
	@rm -rf $(BUILDDIR)
	@rm -rf $(LIBDIR)/*/*.a

fclean: clean
	@rm -rf $(LIBDIR)/*/build
	@rm -f $(NAME)
	@if [ "./" != "$(dir $(TARGET))" ]; then rm -rf $(dir $(TARGET)); fi

re: fclean all

debug: CFLAGS += -g -fsanitize=address -D DEBUG=1
debug: all
	@printf "$(RED)Compiled in debug / fsanitize=adress mode!!!$(RESET)\n\n"

leaks: CFLAGS += -D DEBUG=2
leaks: all
	@printf "$(RED)Compiled in debug / leaks mode!!!$(RESET)\n\n"

extra: CFLAGS += -D EXTRA=1
extra: all
	@printf "$(RED)Compiled in extra mode!!!$(RESET)\n\n"

.PHONY: CFLAGS all clean fclean re
