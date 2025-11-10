/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:12:59 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/10 13:56:06 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray(t_window *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH_DISPLAY - 1;
	ray->ray_dir_x = game->player->dir_x + game->player->plane_x * ray->camera_x;
	ray->ray_dir_y = game->player->dir_y + game->player->plane_y * ray->camera_x;
	ray->map_x = (int)game->player->x;
	ray->map_y = (int)game->player->y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->y) * ray->delta_dist_y;
	}
}

void    perform_dda(t_window *game, t_ray *ray)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
		 if (ray->map_y < 0 || ray->map_x < 0)
            break;
        if (!game->parsed_map->map[ray->map_y])
            break;
        if (ray->map_x >= (int)ft_strlen(game->parsed_map->map[ray->map_y]))
            break;
        // Vérification du mur
        if (game->parsed_map->map[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}

void	calculate_wall_height(t_window *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->per_wall_dist = (ray->map_x - game->player->x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->per_wall_dist = (ray->map_y - game->player->y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(HEIGHT_DISPLAY / ray->per_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT_DISPLAY / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT_DISPLAY / 2;
	if (ray->draw_end >= HEIGHT_DISPLAY)
		ray->draw_end = HEIGHT_DISPLAY - 1;
}

void    draw_wall_column(t_window *game, t_ray *ray, int x)
{
    int y;
    t_img   *texture;
    int tex_x;
    double  wall_x;
    double  step;
    double  tex_pos;
    int tex_y;
    int color;
    
    // Choisir la texture selon l'orientation du mur
    if (ray->side == 0 && ray->ray_dir_x > 0)
        texture = game->texture->east;
    else if (ray->side == 0 && ray->ray_dir_x < 0)
        texture = game->texture->west;
    else if (ray->side == 1 && ray->ray_dir_y > 0)
        texture = game->texture->south;
    else
        texture = game->texture->north;
    
    if (ray->side == 0)
        wall_x = game->player->y + ray->per_wall_dist * ray->ray_dir_y;
    else
        wall_x = game->player->x + ray->per_wall_dist * ray->ray_dir_x;
    wall_x -= floor(wall_x);  
    tex_x = (int)(wall_x * (double)texture->width);
    if (ray->side == 0 && ray->ray_dir_x > 0)
        tex_x = texture->width - tex_x - 1;
    if (ray->side == 1 && ray->ray_dir_y < 0)
        tex_x = texture->width - tex_x - 1;
    y = 0;
    while (y < ray->draw_start)
    {
        my_mlx_pixel_put(game->img_ray, x, y, game->texture->ceiling);
        y++;
    }
    step = 1.0 * texture->height / ray->line_height;
    tex_pos = (ray->draw_end - HEIGHT_DISPLAY / 2 + ray->line_height / 2) * step;
    while (y <= ray->draw_end)
    {
        tex_y = (int)tex_pos & (texture->height - 1);
        tex_pos += step;
        color = *(int *)(texture->addr + (tex_y * texture->line_len + tex_x * (texture->bpp / 8)));
        my_mlx_pixel_put(game->img_ray, x, y, color);
        y++;
    }
    while (y < HEIGHT_DISPLAY)
    {
        my_mlx_pixel_put(game->img_ray, x, y, game->texture->floor);
        y++;
    }
}

void    cast_all_rays(t_window *game)
{
    int x;
    t_ray ray;
    
    /* // Initialise l'image à noir (ou n'importe quelle couleur de test)
    int i = 0;
    while (i < WIDTH_DISPLAY * HEIGHT_DISPLAY)
    {
        ((int *)game->img_ray->addr)[i] = 0x000000; // Noir
        i++;
    }
     */
    x = 0;
    while (x < WIDTH_DISPLAY)
    {
        init_ray(game, &ray, x);
        perform_dda(game, &ray);
        calculate_wall_height(game, &ray);
        draw_wall_column(game, &ray, x);
        x++;
    }
}

