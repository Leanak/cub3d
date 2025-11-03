# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 13:04:31 by lenakach          #+#    #+#              #
#    Updated: 2025/10/29 13:50:20 by lenakach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Nom de l'exec
NAME = cub3d

#Compilateur et flags
CC = cc
FLAGS = -Wall -Wextra -Werror -g3

#Dossiers
SRC_DIR = src
DIV_DIR = divers
LIBFT_DIR = libft

#Includes
INCLUDES = -Iincludes -I$(LIBFT_DIR)/includes

#Bibliotheques
LIBFT = $(LIBFT_DIR)/libft.a

#Sources
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/map_utils.c $(SRC_DIR)/map_parsing.c \
		$(SRC_DIR)/get_texture.c $(SRC_DIR)/utils.c $(SRC_DIR)/free.c \
		$(SRC_DIR)/map_spaces.c $(SRC_DIR)/map_walls.c $(SRC_DIR)/texture_utils.c \

DIVERS = $(DIV_DIR)/print.c
SRCS = $(SRC) $(DIVERS)
OBJS = $(SRCS:.c=.o)
 
#Commandes
RM = rm -f

#Regles
all : $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Compilation de LIbft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re test