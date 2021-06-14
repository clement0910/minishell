NAME = Minishell

ifdef COUNT
T := $(shell $(MAKE) $(NAME) --no-print-directory \
		-nrR \
		PROGRESS="COUNTTHIS" | grep -c "COUNTTHIS")
N := x
C = $(words $N)$(eval N := x $N)
PROGRESS = [`expr $C '*' 100 / $T`%%]
endif

#directories
OBJS_DIR = objs/
SRCS_DIR = srcs/
INCLUDES_HDS = includes/

#libft

LFT_DIR = libft/
LFT = $(LFT_DIR)libft.a
LFT_INCLUDES = $(LFT_DIR)includes/
LFT_INCLUDES_FLAG = -I $(LFT_INCLUDES)
LFT_FLG = -L$(LFT_DIR) -lft

LIB_FLAG = $(LFT_FLG)
LIB_INCLUDES = $(LFT_INCLUDES_FLAG)

#sources

SRCS_FILES =	shell_main.c	\
				shell_location.c \
				built_in_echo.c \
				built_in_cd.c \
				built_in_pwd.c \
				shell_welcome.c \
				shell_cursor.c \
				shell_quit.c	\
				shell_env.c		\
				shell_env_utils.c \
				shell_env_addback.c \
				shell_parse.c	\
				shell_built_in.c \
				shell_init.c	\
				shell_utils.c	\
				built_in_export.c	\
				built_in_env.c	\
				built_in_unset.c	\
				shell_command.c \
                built_in_ls.c \
                shell_sort_export.c 

SRCS = $(SRCS_FILES)

#Headers

INCLUDES =	shell.h	\
			shell_env.h	\
			shell_parse.h	\
			shell_builtin.h	\

INCLUDES := $(addprefix $(INCLUDES_HDS), $(INCLUDES))

ALL_INCLUDES := -I $(INCLUDES_HDS) \
				$(LIB_INCLUDES)		\

#objs

OBJS :=	$(addprefix $(OBJS_DIR),$(SRCS:.c=.o))

#display

HIDE_CURSOR := \e[?25l
SHOW_CURSOR := \e[?25h
CURSOR_LEFT := \e[1000D
ERASE_ENDLINE := \e[K
ERASE_FULLLINE := \e[2K

#global variable

CC = clang
CFLAGS = -O0
RM = /bin/rm -rf
PRINT = printf

all: premake

premake: $(OBJS_DIR) libmake_libft
	@$(MAKE) -s $(NAME) --no-print-directory COUNT=1

libmake_libft:
	@cd $(LFT_DIR) && $(MAKE) -s

lib_clean:
	@cd $(LFT_DIR) && $(MAKE) -s clean

lib_fclean:
	@cd $(LFT_DIR) && $(MAKE) -s fclean

$(OBJS_DIR):
	@mkdir -p $@

show_cursor:
	@printf "\033[0;32mCursor Printed. \033[0m$(SHOW_CURSOR)\n"

$(NAME):	$(OBJS) $(INCLUDES) $(LFT)
	@$(PRINT) "$(ERASE_FULLLINE)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n$(SHOW_CURSOR)" "Compiled" "$(NAME)"
	$(CC) $(CLFAGS) -o $(NAME) $(OBJS) $(LIB_FLAG)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(INCLUDES) $(LFT)
	@$(PRINT) "$(HIDE_CURSOR)\033[1;34m%-20s\033[1;33m%-25s\033[0;32m$(PROGRESS)\033[0m$(ERASE_ENDLINE)$(CURSOR_LEFT)" "Compilation..." "$(NAME)"
	$(CC) $(CFLAGS) -c $(ALL_INCLUDES) -o $@ $<

clean: lib_clean
	@$(RM) $(OBJS_DIR)
	@$(PRINT) "\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n" "Cleaning objects" "$(NAME)"

clean_without_lib:
	@$(RM) $(OBJS_DIR)
	@$(PRINT) "\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n" "Cleaning objects" "$(NAME)"

fclean: clean_without_lib lib_fclean
	@$(RM) $(NAME)
	@$(PRINT) "\033[1;34m%-20s\033[1;33m%-25s\033[0;32m[OK]\033[0m\n" "Cleaning executable" "$(NAME)"

re: fclean all

debug:
	gcc -g3 -fsanitize=address srcs/*.c libft/srcs/*/*.c -I includes -I libft/includes -o Minishell