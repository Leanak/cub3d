/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:12:59 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/09 18:44:58 by lenakach         ###   ########.fr       */
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
    int color;
    
    // 1. Dessine le PLAFOND (du haut jusqu'au début du mur)
    y = 0;
    while (y < ray->draw_start)
    {
        my_mlx_pixel_put(game->img_ray, x, y, game->texture->ceiling);
        y++;
    }
    
    // 2. Dessine le MUR
    if (ray->side == 0)
        color = 0xFF0000;
    else
        color = 0xFFFF00;    
    while (y <= ray->draw_end)
    {
        my_mlx_pixel_put(game->img_ray, x, y, color);
        y++;
    }
    
    // 3. Dessine le SOL (de la fin du mur jusqu'en bas)
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
    
    // Initialise l'image à noir (ou n'importe quelle couleur de test)
    int i = 0;
    while (i < WIDTH_DISPLAY * HEIGHT_DISPLAY)
    {
        ((int *)game->img_ray->addr)[i] = 0x000000; // Noir
        i++;
    }
    
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

