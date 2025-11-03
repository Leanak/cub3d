/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:23:32 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/27 13:24:57 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	side_line_wall(char *str)
{
	int	len;
	int	i;
	
	i = -1;
	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		len--;
	while (++i < len)
		if (str[i] != '1')
			return (0);
	return (1);
}

int	middle_line_wall(char **map)
{
	int	i;
	int	len;
	int	lines;

	i = 1;
	lines = count_true_line(map);
	while (i < lines - 1)
	{
		len = ft_strlen(map[i]);
		if (map[i][len - 1] == '\n')
			len--;
		if (map[i][0] != '1' || map[i][len - 1] != '1')
		{
			printf("HERE ??? %d\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_walls(char **map)
{
	int	lines;

	lines = count_true_line(map);
	if (!side_line_wall(map[0]) || !side_line_wall(map[lines - 1]))
		return (0);	
	if (!middle_line_wall(map))
		return (0);
	return (1);
}
