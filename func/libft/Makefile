# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 15:17:46 by hhagiwar          #+#    #+#              #
#    Updated: 2023/09/24 19:12:32 by hhagiwar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# SRCS = ft_isalpha.c \
#     ft_isdigit.c \
#     ft_isalnum.c \
#     ft_isascii.c \
#     ft_isprint.c \
#     ft_strlen.c \
#     ft_memset.c \
#     ft_bzero.c \
#     ft_memcpy.c \
#     ft_memmove.c \
#     ft_strlcpy.c \
#     ft_strlcat.c \
#     ft_toupper.c \
#     ft_tolower.c \
#     ft_strchr.c \
#     ft_strrchr.c \
#     ft_strncmp.c \
#     ft_strnstr.c \
#     ft_memchr.c \
#     ft_memcmp.c \
#     ft_atoi.c \
#     ft_itoa.c \
#     ft_calloc.c \
#     ft_strdup.c \
#     ft_substr.c \
#     ft_strjoin.c \
#     ft_strtrim.c \
#     ft_strmapi.c \
#     ft_striteri.c \
#     ft_putchar_fd.c \
#     ft_putstr_fd.c \
#     ft_putendl_fd.c \
#     ft_putnbr_fd.c \
#     ft_split.c
    
SRCS =ft_strcmp.c \
    ft_putstr_fd.c \
    ft_split.c

SRCS_B = ft_lstnew.c \
    ft_lstadd_front.c \
    ft_lstsize.c \
    ft_lstlast.c \
    ft_lstadd_back.c \
    ft_lstdelone.c \
    ft_lstclear.c \
    ft_lstiter.c \
    ft_lstmap.c
    
OBJS = ${SRCS:.c=.o}
OBJS_B = ${SRCS_B:.c=.o}

ifdef WITH_BONUS
    OBJS += ${OBJS_B}
endif

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -f
LIBC  = ar rc

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} ${RMFLAGS} ${OBJS} ${OBJS_B}
    
fclean: clean
	${RM} ${RMFLAGS} ${NAME}
re: fclean all

bonus:
	make WITH_BONUS=1

.PHONY: bonus all clean fclean re
