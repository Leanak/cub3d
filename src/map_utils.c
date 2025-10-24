/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:47:01 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/20 16:25:25 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_line(int fd)
{
	int		count;
	char	*line;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

void	create_map(char **map, int fd)
{
	int		i;
	char	*line;

	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map[i] = line;
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	close(fd);
}

/* char	**read_map(char *filename, t_window	*game)
{
	int fd;
	char **map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	game->nbr_line = count_line(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * (game->nbr_line + 1));
	if (!map)
		return (close(fd), NULL);
	create_map(map, fd);
	//if (!map_parsing(map, game))
	//	return (close(fd), NULL);
	close(fd);
	return (map);
} */

