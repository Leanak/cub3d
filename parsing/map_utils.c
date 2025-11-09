/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:47:01 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/05 14:08:57 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*strdup_without_n(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	else
	{
		while (src[i] && src[i] != '\n')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (dest);
}

int	count_true_line(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	size_map(t_mapping *game, char *filename, int count)
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
