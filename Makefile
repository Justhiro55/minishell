# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/24 19:00:50 by hhagiwar          #+#    #+#              #
#    Updated: 2023/10/05 16:26:06 by hhagiwar         ###   ########.fr        #
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
		src/command/not_found_command.c
		

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
# notdir 関数は、パスからディレクトリ部分を削除してファイル名だけを取得する関数
# addprefix 関数は、第一引数に指定した文字列を、第二引数に指定した文字列の前に付ける関数

LIBFTDIR	=	libft
LIBFT		=	func/$(LIBFTDIR)/libft.a
LIB			=	$(LIBFT)

GNLDIR = get_next_line
GNL_SRC = func/$(GNLDIR)/get_next_line.c func/$(GNLDIR)/get_next_line_utils.c
GNL = ${GNL_SRC}

all: $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/command/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	make -C func/${LIBFTDIR}
	$(CC) -lreadline ${LIB} ${GNL} $(OBJ) -o $(NAME)
	@printf "\e[38;5;82msuccessfully built🚀\e[0m\n"

clean: 
	$(RM) $(RMFLAGS) ${OBJ}
	make clean -C func/${LIBFTDIR}
    
fclean: clean 
	$(RM) $(RMFLAGS) $(NAME) a.out
	@printf "\e[38;5;208msuccessfully deleted🗑\e[0m\n"

push: 
	git add .
	git commit -m "auto commit"
	git push

re: fclean all 

.PHONY: all clean fclean re help

