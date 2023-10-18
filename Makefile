# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/24 19:00:50 by hhagiwar          #+#    #+#              #
#    Updated: 2023/10/18 18:55:24 by hhagiwar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -f
SRC = src/main.c \
		src/command/command.c \
		src/command/cd_command.c \
		src/command/echo_command.c \
		src/command/env_command.c \
		src/command/exit_command.c \
		src/command/pwd_command.c \
		src/command/not_found_command.c \
		src/command/set_env.c \
		src/command/ls_command.c \
		src/command/export_command.c

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

$(OBJ_DIR)/%.o: src/command/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@printf "\e[38;5;82m----Compiling libft----\e[0m\n"
	@make -C func/${LIBFTDIR}
	@$(CC) -lreadline ${LIB} ${GNL} $(OBJ) -o $(NAME)
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

