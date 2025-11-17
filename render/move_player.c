/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:53:32 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/17 13:06:44 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_collision(t_window *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	
	// Vérifie que les coordonnées sont dans les limites
	if (new_y < 0 || new_x < 0)
		return (0);
	
	// Vérifie que la ligne existe
	if (!game->parsed_map->map[map_y])
		return (0);
	
	// Vérifie que la colonne existe dans cette ligne
	if (map_x >= (int)ft_strlen(game->parsed_map->map[map_y]))
		return (0);
	
	// Vérifie qu'il n'y a pas de mur
	if (game->parsed_map->map[map_y][map_x] == '1')
		return (0);
	
	return (1);
}

void	move_player(t_window *game)
{
	t_player *p;
	double move_speed = 3.0 * game->delta_time;
	double	rot_speed = 2.0 * game->delta_time;
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
		if (check_collision(game, new_x, new_y))
		{
			p->x = new_x;
			p->y = new_y;
		}
	}
	if (p->move_backward)
	{
		new_x = p->x - p->dir_x * move_speed;
		new_y = p->y - p->dir_y * move_speed;
		if (check_collision(game, new_x, new_y))
		{
			p->x = new_x;
			p->y = new_y;
		}
	}
	if (p->move_left)
	{
		new_x = p->x - p->plane_x * move_speed;
		new_y = p->y - p->plane_y * move_speed;
		if (check_collision(game, new_x, new_y))
		{
			p->x = new_x;
			p->y = new_y;
		}
	}
	if (p->move_right)
	{
		new_x = p->x + p->plane_x * move_speed;
		new_y = p->y + p->plane_y * move_speed;
		if (check_collision(game, new_x, new_y))
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
		p->plane_y = old_plane_x * sin(-rot_speed) + p->plane_x * cos(-rot_speed);
	}
	if (p->turn_right)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
		p->dir_y = old_dir_x * sin(rot_speed) + p->dir_y * cos(rot_speed);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
		p->plane_y = old_plane_x * sin(rot_speed) + p->plane_x * cos(rot_speed);
	}
}