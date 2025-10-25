/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:15:20 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/25 19:27:47 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_game(t_window **game, char *filename)
{
	*game = malloc(sizeof(t_window));
	if (!game)
		return (0);
	(*game)->fd = open(filename, O_RDONLY);
	if ((*game)->fd < 0)
		return (free((*game)), 0);
	(*game)->texture = NULL;
	(*game)->map = NULL;
	(*game)->map_size = 0;
	(*game)->nbr_line = 0;
	(*game)->texture = NULL;
	return (1);
}

int	check_extension(char *filename)
{
	while (*filename && *filename != '.')
		filename++;
	if (!ft_strncmp(filename, ".cub", 4))
	{
		filename += 4;
		if (*filename == '\0')
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_window *game;
	int	start_map;

	start_map = 0;
	game = NULL;
	if (ac != 2 || !*av[1])
		return (1);
	if (!check_extension(av[1]))
		return (1);
	if (!init_game(&game, av[1]))
		return (1);
	start_map = get_texture(game, av[1]);
	if (start_map == 0)
		return (free_all(game), 1);
	else
	{
		printf("START MAP : %d\n", start_map);
		//map_parsing(start_map, game);
		free_all(game);
	}
	return (0);
}
