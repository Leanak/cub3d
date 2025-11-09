/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:15:20 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/08 12:20:32 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_game(t_mapping **parsed_map, char *filename)
{
	*parsed_map = malloc(sizeof(t_mapping));
	if (!parsed_map)
		return (0);
	(*parsed_map)->fd = open(filename, O_RDONLY);
	if ((*parsed_map)->fd < 0)
		return (free((*parsed_map)), 0);
	(*parsed_map)->texture = NULL;
	(*parsed_map)->map = NULL;
	(*parsed_map)->map_size = 0;
	(*parsed_map)->lines = 0;
	(*parsed_map)->texture = NULL;
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
	t_mapping	*parsed_map;
	int			start_map;

	start_map = 0;
	parsed_map = NULL;
	if (ac != 2 || !*av[1])
		return (1);
	if (!check_extension(av[1]))
		return (1);
	if (!init_game(&parsed_map, av[1]))
		return (1);
	if (!get_texture_and_map(parsed_map, av[1]))
		return (free_all(parsed_map), 1);
	else
	{
		if (!start_cub(parsed_map))
			return (free_all(parsed_map), 1);
		free_all(parsed_map);
	} 
	return (0);
}
