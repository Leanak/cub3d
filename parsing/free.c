/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:17:12 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/08 10:29:19 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_gnl_split_line(char **split, char *line)
{
	if (line)
		free(line);
	free_split(split);
	get_next_line(-1);
}

void	free_texture(t_texture_tmp *texture)
{
	t_texture_tmp	*tmp;

	tmp = texture;
	if (!texture)
		return ;
	while (texture)
	{
		tmp = texture->next;
		free(texture->path);
		free(texture);
		texture = tmp;
	}
}


void	free_all(t_mapping *game)
{
	if (!game)
		return ;
	if (game->fd > 2)
		close(game->fd);
	free_split(game->map);
	free_texture(game->texture);
	free(game);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

