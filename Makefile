# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 13:04:31 by lenakach          #+#    #+#              #
#    Updated: 2025/11/09 18:53:47 by lenakach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Nom de l'exec
NAME = cub3d

#Compilateur et flags
CC = cc
FLAGS = -Wall -Wextra -Werror -g3

#Dossiers
PARS_DIR = parsing
DIV_DIR = divers
LIBFT_DIR = libft
RENDER_DIR = render
MINILIBX_DIR = minilibx-linux


#Includes
INCLUDES = -Iincludes -I$(LIBFT_DIR)/includes -I$(MINILIBX_DIR)

#Bibliotheques
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MINILIBX_DIR)/libmlx.a
MLX_FLAGS = -L$(MINILIBX_DIR) -lmlx -L/usr/libX11 -lXext -lX11 -lm -lz

#Sources
PARS = $(PARS_DIR)/main.c $(PARS_DIR)/map_utils.c $(PARS_DIR)/map_parsing.c \
		$(PARS_DIR)/get_texture.c $(PARS_DIR)/utils.c $(PARS_DIR)/free.c \
		$(PARS_DIR)/map_spaces.c $(PARS_DIR)/map_walls.c $(PARS_DIR)/texture_utils.c \
		$(PARS_DIR)/elements_utils.c
RENDER = $(RENDER_DIR)/start_render.c $(RENDER_DIR)/player_init.c $(RENDER_DIR)/pixel.c \
			$(RENDER_DIR)/texture_init.c $(RENDER_DIR)/raycasting.c $(RENDER_DIR)/key.c \
			$(RENDER_DIR)/move_player.c

DIVERS = $(DIV_DIR)/print.c
PARSING = $(PARS) $(DIVERS)
ALL = $(PARSING) $(RENDER)
OBJS = $(ALL:.c=.o)

#Commandes
RM = rm -f

#Regles
all : $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@echo "Compilation de LIbft..."
	@make -C $(LIBFT_DIR)

$(MLX):
	@echo "Compilation de MiniLibX"
	@make -C $(MINILIBX_DIR)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -lm

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