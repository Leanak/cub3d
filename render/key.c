/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:46:57 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/17 13:11:56 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_window *game)
{
	printf("Key pressed: %d\n", keycode); // DEBUG
	if (keycode == 65307) //ESC
		exit(0);
	if (keycode == 'w')
	{
		game->player->move_forward = 1;
		printf("Forward = 1\n"); // DEBUG
	}
	if (keycode == 's')
	{
		game->player->move_backward = 1;
		printf("BackWard = 1\n"); // DEBUG
	}
	if (keycode == 'a')
	{
		game->player->move_left = 1;
		printf("Left = 1\n"); // DEBUG
	}
	if (keycode == 'd')
	{
		game->player->move_right = 1;
		printf("Right = 1\n"); // DEBUG
	}
	if (keycode == 65361)
	{
		game->player->turn_left = 1;
		printf("Turn left = 1\n"); // DEBUG
	}
	if (keycode == 65363)
	{
		game->player->turn_right = 1;
		printf("Turn Right = 1\n"); // DEBUG
	}
	return (0);
}

int	key_release(int keycode, t_window *game)
{
	printf("Key released: %d\n", keycode); // DEBUG
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