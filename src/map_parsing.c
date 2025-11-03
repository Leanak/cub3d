/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:44:35 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/03 20:22:29 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_parsing(t_window *game)
{
	if (!change_spaces(game->map))
		return (0);
	if (!check_walls(game->map))
		return (0);
	//que 6 caracteres possibles
	return (1);
}

int	get_map(t_window *game, char **line)
{
	int	i;
	
	i = 0;
	game->map = malloc((sizeof(char *)) * ((game->map_size + 1) + 1));
	if (!game->map)
		return (0);
	while (*line)
	{
		game->map[i] = ft_strdup(*line);
		if (!game->map[i])
			return (0);
		free(*line);
		*line = get_next_line(game->fd);
		i++;
	}
	game->map[i] = NULL;
	return (1);
}
