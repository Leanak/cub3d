/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:58:44 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/17 13:17:15 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_dir(t_player *player, char **map)
{
	int	i;
	int	j;
	int	len;
	
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (map[i][len - 1] == '\n')
			len--;
		j = 0;
		while (j < len)
		{
			if (ft_strchr("NSWE", map[i][j]))
			{
				player->x = j + 0.5;
				player->y = i + 0.5;
				if (map[i][j] == 'N')
				{
					player->dir_x = 0;
					player->dir_y = -1;
					player->plane_x = 0.66;
					player->plane_y = 0;
				}
				else if (map[i][j] == 'S')
				{
					player->dir_x = 0;
					player->dir_y = 1;
					player->plane_x = -0.66;
					player->plane_y = 0;
				}
				else if (map[i][j] == 'E')
				{
					player->dir_x = 1;
					player->dir_y = 0;
					player->plane_x = 0;
					player->plane_y = 0.66;
				}
				else if (map[i][j] == 'W')
				{
					player->dir_x = -1;
					player->dir_y = 0;
					player->plane_x = 0;
					player->plane_y = -0.66;
				}
				return ;
			}
			j++;
		}
		i++;
	}
}

int	init_champs(t_window *game)
{
	game->player->move_forward = 0;
	game->player->move_backward = 0;
	game->player->move_left = 0;
	game->player->move_right = 0;
	game->player->turn_left = 0;
	game->player->turn_right = 0;
	return (1);
}

int	init_player(t_window *game)
{
	set_dir(game->player, game->parsed_map->map);
	init_champs(game);
    return (1);
}
