# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 13:53:25 by hhagiwar          #+#    #+#              #
#    Updated: 2023/11/25 22:37:33 by kotainou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
INCLUDES_DIR = ./includes
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
		src/lexer/lexer_utils.c \
		src/lexer/syntax_error.c \
		src/parser/parser.c \
		src/parser/parser_redirect.c \
		src/parser/parser_utils.c

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

$(NAME): $(OBJ)
	@printf "\e[38;5;82m----Compiling libft----\e[0m\n"
	@make -C func/${LIBFTDIR}
	@$(CC) $(CFLAGS) -lreadline ${LIB} ${GNL} $(OBJ) -o $(NAME)
	@printf "\e[38;5;82m  minishell Compiled🚀\e[0m\n\n"

#	@$(CC) -lreadline ${LIB} ${GNL} $(OBJ) -o $(NAME)

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
