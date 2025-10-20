/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:15:20 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/20 12:52:52 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_line(int fd)
{
	int	count;
	char	*line;
	
	count = 0;
	while (1)
	{
		line = get_next
	}
}

char	**read_map(char *filename)
{
	int	fd;
	int	nbr_line;
	char	**map;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	nbr_line = count_line(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * (nbr_line + 1));
	if (!map)
		return (NULL);
}

int	init_game(t_window *game)
{
	game = malloc(sizeof(t_window));
	if (!game)
		return (0);
	ft_bzero(game, sizeof(t_window));
	return (1);
}

int	main(int ac, char **av)
{
	t_window		*game;

	if (ac != 2 || !*av[1] || !init_game(game))
		return (1);
	game->map = read_map(av[1]);
	if (!game->map)
		return (free(game), 1);
	return (0);
}