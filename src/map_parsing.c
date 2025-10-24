/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:44:35 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/21 15:03:57 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_parsing(char **map, t_window *game)
{
	int	len;

	len = ft_strlen(map[0]);
	if (map[0][len - 1] == '\n')
		game->true_len = len--;
	else
		game->true_len = len;
	return (0);
}


