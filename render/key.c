/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:46:57 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/10 15:26:39 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_window *game)
{
	if (keycode == 65307) //ESC
		exit(0);
	if (keycode == 'w')
		game->player->move_forward = 1;
	if (keycode == 's')
		game->player->move_backward = 1;
	if (keycode == 'a')
		game->player->move_left = 1;
	if (keycode == 'd')
		game->player->move_right = 1;
	if (keycode == 65361)
		game->player->turn_left = 1;
	if (keycode == 65363)
		game->player->turn_right = 1;
	return (0);
}

int	key_release(int keycode, t_window *game)
{
	if (keycode == 'w')
		game->player->move_forward = 0;
	if (keycode == 's')
		game->player->move_backward = 0;
	if (keycode == 'a')
		game->player->move_left = 0;
	if (keycode == 'd')
		game->player->move_right = 0;
	if (keycode == 65361)
		game->player->turn_left = 0;
	if (keycode == 65363)
		game->player->turn_right = 0;
	return (0);
}
