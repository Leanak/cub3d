/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:15:38 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/10 15:18:13 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Librairies
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
#include <sys/time.h>

// Variables globales
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef WIDTH_DISPLAY
#  define WIDTH_DISPLAY 1024
# endif

# ifndef HEIGHT_DISPLAY
#  define HEIGHT_DISPLAY 768
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 64
# endif

// Structures
typedef enum e_texture_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}							t_texture_type;

typedef struct s_texture_tmp
{
	char					*path;
	t_texture_type			type;
	struct s_texture_tmp	*next;

}							t_texture_tmp;

typedef struct s_mapping
{
	char					**map;
	int						fd;
	int						map_size;
	int						lines;
	t_texture_tmp			*texture;
}							t_mapping;

typedef struct s_img
{
	void					*img;
	char					*addr;
	int						bpp;
	int						line_len;
	int						endian;
	int						height;
	int						width;
}							t_img;

typedef struct s_texture
{
	t_img					*north;
	t_img					*south;
	t_img					*east;
	t_img					*west;
	int						floor;
	int						ceiling;
}							t_texture;

typedef struct s_player
{
	double					x;
	double					y;
	double dir_x; // en radians, dans quelle dir le player regarde
	double					dir_y;
	double plane_x; // sa camera, ou field of view
	double					plane_y;
	int						move_forward;
	int						move_backward;
	int						move_left;
	int						move_right;
	int						turn_left;
	int						turn_right;
}							t_player;

typedef struct s_ray
{
	double camera_x;      // Position x dans le plan camera de -1 a 1
	double ray_dir_x;     // Direction du rayon x
	double ray_dir_y;     // Direction du rayon Y
	int map_x;            // Case X actuelle dans la map
	int map_y;            // Case Y actuelle dans la map
	double side_dist_x;   // Distance jusqu'au prochain cote X
	double side_dist_y;   // Distance jusqu'au prochaine cote Y
	double delta_dist_x;  // Distance entre 2 cotes X
	double delta_dist_y;  // Distance entre 2 cotes Y
	int step_x;           // Direction de marche (-1 ou + 1)
	int step_y;           // Direction de marche (-1 ou + 1)
	int hit;              // Mur touche
	int side;             // Cote touche (0 = NS, 1 = EW);
	double per_wall_dist; // Distance perpendiculaire au mur
	int line_height;      // Hauteur a dessiner
	int draw_start;       // Pixel Y de debut
	int draw_end;         // Pixel Y de fin
}							t_ray;

typedef struct s_window
{
	void					*mlx;
	void					*mlx_win;
	double	delta_time;
	double	last_frame_time; 
	t_img					*img_ray;
	t_player				*player;
	t_mapping				*parsed_map;
	t_texture				*texture;
}							t_window;

// Map parsing
int							get_map(t_mapping *game, char **line);
int							map_parsing(t_mapping *game);

// Map utils
int							size_map(t_mapping *game, char *filename,
								int count);
int							count_true_line(char **map);
char						*strdup_without_n(const char *src);

// Map spaces
int							change_spaces(char **old_map);
char						*delete_spaces(char *str);
int							count_spaces(char *str);

// Map walls
int							side_line_wall(char *str);
int							middle_line_wall(char **map);
int							check_walls(t_mapping *game);

// Get texture
int							get_texture_and_map(t_mapping *game,
								char *filename);

// Texture utils
int							format_rgb(t_texture_tmp *texture);
int							is_alldigit(char *str);
int							split_len(char **split);

// Utils
int							ft_lstlen(t_texture_tmp *texture);
void						error(char *str);

// Free
void						free_split(char **split);
void						free_texture(t_texture_tmp *texture);
void						free_all(t_mapping *game);
void						free_gnl_split_line(char **split, char *line);

// Elements utils
int							check_elements(t_mapping *game);

// Start render
int							start_cub(t_mapping *game);

// Player Init
int							init_player(t_window *game);

// Pixel
void						my_mlx_pixel_put(t_img *img, int x, int y,
								int color);

// Texture Init
int							load_all_texture(t_window *game);

// Ray casting
void						cast_all_rays(t_window *game);

// Key
int							key_press(int keycode, t_window *game);
int							key_release(int keycode, t_window *game);

// Move Player
void						move_player(t_window *game);

// Divers
void						print_map(char **map);
void						print_texture(t_texture_tmp *texture);

#endif