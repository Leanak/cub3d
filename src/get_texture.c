/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:48:26 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/24 14:38:55 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_texture	*create_node(char **split)
{
	t_texture	*new_node;

	if (!split || !split[0] || !split[1])
		return (NULL);
	new_node = malloc(sizeof(t_texture));
	if (!new_node)
		return (NULL);
	if (!ft_strncmp(split[0], "NO", 2))
		new_node->type = NO;
	else if (!ft_strncmp(split[0], "SO", 2))
		new_node->type = SO;
	else if (!ft_strncmp(split[0], "WE", 2))
		new_node->type = WE;
	else if (!ft_strncmp(split[0], "EA", 2))
		new_node->type = EA;
	else if (!ft_strncmp(split[0], "F", 1))
		new_node->type = F;
	else if (!ft_strncmp(split[0], "C", 1))
		new_node->type = C;
	else
	{
		printf("ICI ? \n");
		return (NULL);
	}
	new_node->path = ft_strdup(split[1]);
	new_node->next = NULL;
	return (new_node);
}

int	add_texture(t_texture **head, char **split)
{
	t_texture	*new_node;
	t_texture	*tmp;

	new_node = create_node(split);
	if (!new_node)
		return (0);
	if (!*head)
		*head = new_node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (1);
}

int	get_texture(t_window *game)
{
	int count;
	char *line;
	char **tmp;

	count = 0;
	while (1)
	{
		line = get_next_line(game->fd);
		count++;
		if (!line)
		{
			printf("HEIN ????\n");
			break ;
		}
		if (!ft_strncmp(line, "\n", 1))
		{
			printf("WTFFF??\n");
			continue ;
		}
		tmp = ft_split(line, ' ');
		if (!tmp || tmp[0][0] == '1')
		{
			get_next_line(-1);
			printf("OLD EL PASSO\n");
			free_split(tmp);
			if (line)
				free(line);
			return (0);
		}
		if (!add_texture(&game->texture, tmp))
		{
			get_next_line(-1);
			printf("SUREMENT ICI LOL\n");
			return (free_split(tmp), free(line), 0);
		}
		if (ft_lstlen(game->texture) == 6)
		{
			if (!ft_strncmp(line = get_next_line(game->fd), "\n", 1))
			{
				while (!ft_strncmp(line, "\n", 1))
				{
					free(line);
					line = get_next_line(game->fd);
					count++;
				}
			}
			free(line);
			free_split(tmp);
			return (count);
		}
		get_next_line(-1);
		free_split(tmp);
		free(line);
	}
	printf("GIRLLLL ? \n");
	//free_split(tmp);
	//free(line);
	return (0);
}
