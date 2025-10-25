/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:44:35 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/25 20:08:12 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	size_map(t_window *game, char *filename, int count)
{
	int		fd2;
	int		size;
	int		i;
	char	*line;

	i = -1;
	size = 0;
	fd2 = open(filename, O_RDONLY);
	if (fd2 < 0)
		return (0);
	while (++i < count)
	{
		line = get_next_line(fd2);
		free(line);
	}
	line = get_next_line(fd2);
	while (line && ft_strncmp(line, "\n", 1))
	{
		free(line);
		line = get_next_line(fd2);
		size++;
	}
	close(fd2);
	game->map_size = size;
	return (1);
}

int	get_map(t_window *game, char **line)
{
	int	i;
	
	i = 0;
	game->map = malloc((sizeof(char *)) * ((game->map_size + 1) + 1));
	if (!game->map)
		return (0);
	printf("QUE PASSO CHICO :: %s\n", *line);
	while (*line)
	{
		game->map[i] = *line;
		*line = get_next_line(game->fd);
		i++;
	}
	game->map[i] = NULL;
	print_map(game->map);
	return (1);
}
