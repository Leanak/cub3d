/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:54:38 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/24 11:13:35 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
	printf("FIN DE MAP\n");
}

void	print_texture(t_texture *texture)
{
	t_texture	*tmp;

	tmp = texture;
	while (tmp)
	{
		printf("MON TYPE : %u\n", tmp->type);		
		printf("MON PATH : %s\n", tmp->path);
		tmp = tmp->next;
	}
}