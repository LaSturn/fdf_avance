# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csu-ubuntu <csu-ubuntu@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 10:20:01 by csturny           #+#    #+#              #
#    Updated: 2025/03/17 12:44:51 by csu-ubuntu       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Répertoires des sources et des dépendances
SRCS = srcs/main.c  srcs/errors_msg.c \
		 srcs/map_data.c \
		srcs/render_lines.c srcs/transform_points.c \
		srcs/color_rainbow.c \
		srcs/tile_culling.c \
		srcs/render_utils.c
# Générer la liste des fichiers objets directement dans le répertoire des sources
OBJS = $(SRCS:srcs/%.c=%.o)

NAME    = fdf
CC      = gcc -g
RM      = rm -f

# Répertoires et options d'inclusion
INCLUDES = -Ilibft -Iprintf -Imlx -Isrcs -Iget_next_line
CFLAGS  = -Wall -Wextra -Werror $(INCLUDES)

# Débogage optionnel
DEBUG = 0
ifeq ($(DEBUG), 1)
    CFLAGS += -fsanitize=address
endif

# Répertoires des dépendances
LIBFT_DIR = libft
PRINTF_DIR = printf
MLX_DIR = mlx


# Options pour minilibx sur Linux
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
PRINTF_FLAGS = -L$(PRINTF_DIR) -lftprintf
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

# Cible principale
all: $(NAME)

# Règle pour compiler toutes les bibliothèques avant de compiler l'exécutable
$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

$(PRINTF_DIR)/printf.a:
	make -C $(PRINTF_DIR)

$(MLX_DIR)/libmlx.a:
	make -C $(MLX_DIR)

# Règle de compilation des fichiers objets (directement dans le même répertoire)
%.o: srcs/%.c
	$(CC) $(CFLAGS) -c $< -o $@


# Règle pour générer l'exécutable
$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a $(PRINTF_DIR)/printf.a  $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(PRINTF_FLAGS) $(MLX_FLAGS) -o $(NAME)


# Règles pour les sous-modules (libs externes)
libft:
	make -C $(LIBFT_DIR)

printf:
	make -C $(PRINTF_DIR)

mlx:
	make -C $(MLX_DIR)



# Nettoyage des fichiers objets (directement dans le répertoire source)
clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)
	make clean -C $(MLX_DIR)
	$(RM) $(OBJS)

# Nettoyage complet
fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)
	make fclean -C $(MLX_DIR)
	$(RM) $(NAME)

# Reconstruction complète
re: fclean all

# Cibles spéciales
.PHONY: libft printf mlx all clean fclean re
