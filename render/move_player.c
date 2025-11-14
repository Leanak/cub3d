/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:53:32 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/11 18:01:07 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_collision(t_window *game, double x, double y)
{
    double margin = 0.2;
    int map_y, map_x;
    int dy = -1;

    while (dy <= 1)
    {
        int dx = -1;
        while (dx <= 1)
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

            dx += 2; // équivaut à dx = -1 → +1 → +3 → sortie
        }
        dy += 2; // équivaut à dy = -1 → +1 → +3 → sortie
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