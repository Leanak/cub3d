/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:07:10 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/17 13:13:15 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_frame(t_window *game)
{
	cast_all_rays(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img_ray->img, 0, 0);
}

double	get_time(void)
{
	double	current_time;
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec + tv.tv_usec * 1e-6;
	return (current_time);
}

int	loop_hook(t_window *game)
{
	double	current_time;

	current_time = get_time();
	game->delta_time = current_time - game->old_time;
	game->old_time = current_time;
	if (game->delta_time > 0.05)
		game->delta_time = 0.05;
	if (game->delta_time < 0.001)
		game->delta_time = 0.016; 
	move_player(game);
	render_frame(game);
	return (0);
}

void	draw_floor_ceiling(t_window *game)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < HEIGHT_DISPLAY)
	{
		x = 0;
		while (x < WIDTH_DISPLAY)
		{
			if (y < HEIGHT_DISPLAY/2) // Moitie haute = plafond
				my_mlx_pixel_put(game->img_ray, x, y, game->texture->ceiling);
			else
				my_mlx_pixel_put(game->img_ray, x, y, game->texture->floor);
			x++;
		}
		y++;
	}
}

int	init_window(t_window *window, t_mapping	*parsed_map)
{
	window->mlx = NULL;
	window->mlx_win = NULL;
	window->img_ray = NULL;
	window->mlx = mlx_init();
	if (!window->mlx)
		return (0);
	window->mlx_win = mlx_new_window(window->mlx, WIDTH_DISPLAY, HEIGHT_DISPLAY, "Cub3d");
	if (!window->mlx_win)
		return (error("Window creation failed"), error("\n"), 0);
	window->img_ray = malloc(sizeof(t_img));
	if (!window->img_ray)
		return (0);
	window->img_ray->img = mlx_new_image(window->mlx, WIDTH_DISPLAY, HEIGHT_DISPLAY);
	if (!window->img_ray->img)
		return (1);
	window->img_ray->addr = mlx_get_data_addr(window->img_ray->img,
			&window->img_ray->bpp, &window->img_ray->line_len,
			&window->img_ray->endian);
	if (!window->img_ray->addr)
		return (1);
	window->player = malloc(sizeof(t_player));
	if (!window->player)
		return (0);
	window->parsed_map = parsed_map;
	if (!load_all_texture(window))
		return (0);
	window->old_time = get_time();
	window->delta_time = 0;
	return (1);
}

int	start_cub(t_mapping *parsed_map)
{
	t_window	*game;

	game = malloc(sizeof(t_window));
	if (!game)
		return (0);
	if (!init_window(game, parsed_map))
		return (0);
	if (!init_player(game))
		return (0);
	mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, key_release, game);
	mlx_loop(game->mlx);
	return (1);
}
