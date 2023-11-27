# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 13:53:25 by hhagiwar          #+#    #+#              #
#    Updated: 2023/11/27 18:34:18 by kotainou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#rl_replace_lineが使えるようにmakefileを修正する

NAME = minishell
CC = gcc
INCLUDES_DIR = ./includes
INC	=	$(addprefix -I,$(INCLUDES_DIR)) -I$(RL_INCDIR)
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES_DIR)
# CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES_DIR) -g -fsanitize=address
RM = rm
RMFLAGS = -f
SRC = src/main.c \
		src/exec/command.c \
		src/exec/command_utils.c \
		src/exec/exec_redirect.c \
		src/exec/exec.c \
		src/exec/exec_utils.c \
		src/exec/redirect_utils.c \
		src/exec/redirect_utils2.c \
		src/exec/exit_process.c \
		src/builtin/cd_command.c \
		src/builtin/echo_command.c \
		src/builtin/env_command.c \
		src/builtin/exit_command.c \
		src/builtin/pwd_command.c \
		src/builtin/set_env.c \
		src/builtin/ls_command.c \
		src/builtin/export_command.c \
		src/lexer/lexer.c \
		src/lexer/token.c \
		src/lexer/token_utils.c \
		src/lexer/lexer_utils.c \
		src/lexer/syntax_error.c \
		src/parser/parser.c \
		src/parser/parser_redirect.c \
		src/parser/parser_utils.c \
		src/parser/parser_utils2.c \
		src/signal/signal.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
# notdir 関数は、パスからディレクトリ部分を削除してファイル名だけを取得する関数
# addprefix 関数は、第一引数に指定した文字列を、第二引数に指定した文字列の前に付ける関数

LIBFTDIR	=	libft
LIBFT		=	func/$(LIBFTDIR)/libft.a
LIB			=	$(LIBFT)

all: $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/exec/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/builtin/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/lexer/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/parser/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/signal/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@printf "\e[38;5;82m----Compiling libft----\e[0m\n"
	@make -C func/${LIBFTDIR}
	@$(CC) -lreadline ${LIB} ${GNL} $(OBJ) -L .brew/Cellar/readline/8.2.7/lib/libreadline.a -I .brew/opt/readline/include -o $(NAME)
	@printf "\e[38;5;82m  minishell Compiled🚀\e[0m\n\n"

clean: 
	@$(RM) $(RMFLAGS) ${OBJ}
	@make clean -C func/${LIBFTDIR}
    
fclean: clean 
	@$(RM) $(RMFLAGS) $(NAME) a.out
	@make fclean -C func/${LIBFTDIR}
	@printf "\e[38;5;208m\nsuccessfully deleted🗑\e[0m\n\n"

party:
	@printf "\033c"
	@echo "\n\033[35m♪┏(・o･)┛♪"
	@sleep 1
	@printf "\033c"
	@echo "\033[1;33m♪┗(・o･)┓♪"
	@sleep 1
	@printf "\033c"
	@echo "\n\033[36m♪┏(・o･)┛♪"
	@sleep 1
	@printf "\033c"
	@echo "\033[34m♪┗(・o･)┓♪\n"
	@printf "\033c"

push:
	git add .
	git commit -m "$(MSG)"
	git push

push_w:
	git add .
	git commit -m "wip"
	git push

re: fclean all 

.PHONY: all clean fclean re help

# NAME = minishell

# CC = cc
# CFLAGS = -Wall -Wextra -Werror -MMD -MP
# # CFLAGS += -g -fsanitize=address

# # sanitizeが有る無しで挙動が変わります。。謎

# INCDIR = ./includes
# INC	=	$(addprefix -I,$(INCDIR)) -I$(RL_INCDIR)

# # INC 変数に-I$(RL_INCDIR)を追加
# # readline.h ヘッダーファイルを見つけるためにコンパイラが
# # 使用する検索パスに readline の include ディレクトリが追加されます。
# # 最新版の関数rl_replace_lineが使えるようになります。

# SRCSDIR = ./srcs
# OBJSDIR = ./objs
# SRC = src/main.c \
# 		src/exec/command.c \
# 		src/exec/command_utils.c \
# 		src/exec/exec_redirect.c \
# 		src/exec/exec.c \
# 		src/exec/exec_utils.c \
# 		src/exec/redirect_utils.c \
# 		src/exec/redirect_utils2.c \
# 		src/exec/exit_process.c \
# 		src/builtin/cd_command.c \
# 		src/builtin/echo_command.c \
# 		src/builtin/env_command.c \
# 		src/builtin/exit_command.c \
# 		src/builtin/pwd_command.c \
# 		src/builtin/set_env.c \
# 		src/builtin/ls_command.c \
# 		src/builtin/export_command.c \
# 		src/lexer/lexer.c \
# 		src/lexer/token.c \
# 		src/lexer/token_utils.c \
# 		src/lexer/lexer_utils.c \
# 		src/lexer/syntax_error.c \
# 		src/parser/parser.c \
# 		src/parser/parser_redirect.c \
# 		src/parser/parser_utils.c \
# 		src/signal/signal.c


# OBJS	=	$(patsubst $(SRCSDIR)/%.c,$(OBJSDIR)/%.o,$(SRCS))
# DEPS	=	$(OBJS:.o=.d)

# LIBFTDIR	=	libft
# LIBFT		=	func/$(LIBFTDIR)/libft.a
# # LIB			=	$(LIBFT)
# # LIBFTDIR = ./libft
# # LIBFT	=	$(LIBFTDIR)/libft.a

# UNAME = $(shell uname)

# RL_NAME = readline
# ifeq ($(UNAME),Darwin)
# 	RL_DIR = $(shell brew --prefix readline)
# 	RL_LIBDIR = $(addprefix $(RL_DIR)/,lib)
# 	RL_INCDIR = $(addprefix $(RL_DIR)/,include)
# endif

# LDFLAGS = -L $(LIBFTDIR) -lft -L $(RL_LIBDIR) -l $(RL_NAME)


# all: $(NAME)

# $(NAME): $(OBJS) $(LIBFT)
# 		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

# $(OBJSDIR)/%.o: $(SRCSDIR)/%.c
# 	@mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# $(LIBFT):
# 		$(MAKE) -C $(LIBFTDIR)

# -include $(DEPS)

# clean:
# 		$(MAKE) fclean -C $(LIBFTDIR)
# 		$(RM) $(OBJS) $(DEPS)

# fclean: clean
# 		$(RM) $(NAME)

# re: fclean all

# .PHONY: all clean fclean re bonus
