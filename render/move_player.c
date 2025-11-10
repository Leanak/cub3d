/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:53:32 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/10 15:18:53 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* void	move_player(t_window *game)
{
	t_player *p;
	double move_speed = 0.05;  // ← Réduit de 0.66 à 0.05
	double rot_speed = 0.05;   // ← Réduit de 0.03 à 0.05
	double new_x;
	double new_y;
	double old_dir_x;
	double old_plane_x;
	
	p = game->player;
	
	// Avancer
	if (p->move_forward)
	{
		new_x = p->x + p->dir_x * move_speed;
		new_y = p->y + p->dir_y * move_speed;
		if (game->parsed_map->map[(int)new_y][(int)new_x] != '1')
		{
			p->x = new_x;
			p->y = new_y;
		}
	}
	
	// Reculer
	if (p->move_backward)
	{
		new_x = p->x - p->dir_x * move_speed;
		new_y = p->y - p->dir_y * move_speed;
		if (game->parsed_map->map[(int)new_y][(int)new_x] != '1')
		{
			p->x = new_x;
			p->y = new_y;
		}
	}
	
	// Strafe gauche
	if (p->move_left)
	{
		new_x = p->x - p->plane_x * move_speed;
		new_y = p->y - p->plane_y * move_speed;
		if (game->parsed_map->map[(int)new_y][(int)new_x] != '1')
		{
			p->x = new_x;
			p->y = new_y;
		}
	}
	
	// Strafe droite
	if (p->move_right)
	{
		new_x = p->x + p->plane_x * move_speed;
		new_y = p->y + p->plane_y * move_speed;
		if (game->parsed_map->map[(int)new_y][(int)new_x] != '1')
		{
			p->x = new_x;
			p->y = new_y;
		}
	}
	
	// Tourner à gauche
	if (p->turn_left)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
		p->dir_y = old_dir_x * sin(rot_speed) + p->dir_y * cos(rot_speed);
		
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
		p->plane_y = old_plane_x * sin(rot_speed) + p->plane_y * cos(rot_speed);  // ← CORRIGÉ
	}
	
	// Tourner à droite
	if (p->turn_right)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-rot_speed) - p->dir_y * sin(-rot_speed);
		p->dir_y = old_dir_x * sin(-rot_speed) + p->dir_y * cos(-rot_speed);
		
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-rot_speed) - p->plane_y * sin(-rot_speed);
		p->plane_y = old_plane_x * sin(-rot_speed) + p->plane_y * cos(-rot_speed);  // ← CORRIGÉ
	}
} */

/* int check_collision(t_window *game, double x, double y)
{
    double margin = 0.2; // Marge de sécurité
    
    // Vérifie les 4 coins du joueur
    if (game->parsed_map->map[(int)(y - margin)][(int)(x - margin)] == '1')
        return (1);
    if (game->parsed_map->map[(int)(y - margin)][(int)(x + margin)] == '1')
        return (1);
    if (game->parsed_map->map[(int)(y + margin)][(int)(x - margin)] == '1')
        return (1);
    if (game->parsed_map->map[(int)(y + margin)][(int)(x + margin)] == '1')
        return (1);
    return (0);
} */

int check_collision(t_window *game, double x, double y)
{
    double margin = 0.2;
    int map_y, map_x;

    for (int dy = -1; dy <= 1; dy += 2)
    {
        for (int dx = -1; dx <= 1; dx += 2)
        {
            map_y = (int)(y + dy * margin);
            map_x = (int)(x + dx * margin);
            if (map_y < 0 || map_x < 0)
                return (1); // Hors map = bloqué
            if (!game->parsed_map->map[map_y])
                return (1);
            if (map_x >= (int)ft_strlen(game->parsed_map->map[map_y]))
                return (1);
            if (game->parsed_map->map[map_y][map_x] == '1')
                return (1);
        }
    }
    return (0);
}


void	move_player(t_window *game)
{
	t_player *p;
	double move_speed = 5.0 * game->delta_time;
	double	rot_speed = 3.0 * game->delta_time;
	double new_x;
	double new_y;
	double	old_dir_x;
	double	old_plane_x;
	
	p = game->player;
	//Avancer/Reculer
	if (p->move_forward)
	{
		new_x = p->x + p->dir_x * move_speed;
		new_y = p->y + p->dir_y * move_speed;
		if (!check_collision(game, new_x, new_y))
    	{
        	p->x = new_x;
        	p->y = new_y;
    	}
	}
	if (p->move_backward)
	{
		new_x = p->x - p->dir_x * move_speed;
		new_y = p->y - p->dir_y * move_speed;
		if (!check_collision(game, new_x, new_y))
    	{
        	p->x = new_x;
        	p->y = new_y;
    	}
	}
	if (p->move_left)
	{
		new_x = p->x - p->plane_x * move_speed;
		new_y = p->y - p->plane_y * move_speed;
		if (!check_collision(game, new_x, new_y))
    	{
        	p->x = new_x;
        	p->y = new_y;
    	}
	}
	if (p->move_right)
	{
		new_x = p->x + p->plane_x * move_speed;
		new_y = p->y + p->plane_y * move_speed;
		if (!check_collision(game, new_x, new_y))
    	{
        	p->x = new_x;
        	p->y = new_y;
    	}
	}
	if (p->turn_left)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-rot_speed) - p->dir_y * sin(-rot_speed);
		p->dir_y = old_dir_x * sin(-rot_speed) + p->dir_y * cos(-rot_speed);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-rot_speed) - p->plane_y * sin(-rot_speed);
		p->plane_y = old_plane_x * sin(-rot_speed) + p->plane_y * cos(-rot_speed);
	}
	if (p->turn_right)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
		p->dir_y = old_dir_x * sin(rot_speed) + p->dir_y * cos(rot_speed);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
		p->plane_y = old_plane_x * sin(rot_speed) + p->plane_y * cos(rot_speed);
	}
}