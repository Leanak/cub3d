/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:15:38 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/03 17:03:20 by lenakach         ###   ########.fr       */
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
	t_texture			*texture;
}						t_window;

// Map parsing
int						get_map(t_window *game, char **line);
int						map_parsing(t_window *game);

// Map utils
int						size_map(t_window *game, char *filename, int count);
int						count_true_line(char **map);
char					*strdup_without_n(const char *src);

// Map spaces
int						change_spaces(char **old_map);
char					*delete_spaces(char *str);
int						count_spaces(char *str);

// Map walls
int						side_line_wall(char *str);
int						middle_line_wall(char **map);
int						check_walls(char **map);

// Get texture
int						get_texture_and_map(t_window *game, char *filename);

// Texture utils
int						format_rgb(t_texture *texture);
int						is_alldigit(char *str);
int						split_len(char **split);

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