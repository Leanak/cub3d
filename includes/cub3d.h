/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:15:38 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/25 19:34:13 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Librairies
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <unistd.h>

// Structures
typedef enum e_texture_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}						t_texture_type;

typedef struct s_texture
{
	char				*path;
	t_texture_type		type;
	struct s_texture	*next;

}						t_texture;

typedef struct s_window
{
	char				**map;
	int					fd;
	int					map_size;
	int					nbr_line;
	t_texture			*texture;
}						t_window;

// Map utils

// Map parsing
int						size_map(t_window *game, char *filename, int count);
int						get_map(t_window *game, char **line);

// Get texture
int						get_texture(t_window *game, char *filename);

// Utils
int						ft_lstlen(t_texture *texture);

// Free
void					free_split(char **split);
void					free_texture(t_texture *texture);
void					free_all(t_window *game);
void					free_gnl_split_line(char **split, char *line);

// Divers
void					print_map(char **map);
void					print_texture(t_texture *texture);

#endif