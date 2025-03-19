#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csturny <csturny@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/28 10:34:53 by csturny           #+#    #+#              #
#    Updated: 2025/01/21 14:00:38 by csturny          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC      = clang
CFLAGS  = -Wall -Wextra -Werror -fPIC
RM      = /bin/rm -f

NAME    = libftprintf.a

SRCS    = ft_printf.c ft_specifiers.c ft_specifiers_2.c \

OBJS    = $(SRCS:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "Bibliothèque statique $(NAME) créée avec succès."

clean:
	@$(RM) $(OBJS)
	@echo "Fichiers objets supprimés."

fclean: clean
	@$(RM) $(NAME)
	@echo "Fichiers objets et bibliothèque $(NAME) supprimés."

re: fclean all

.PHONY: all clean fclean re