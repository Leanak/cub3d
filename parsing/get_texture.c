/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:48:26 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/10 15:26:27 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_double(t_texture_tmp *texture)
{
	t_texture_tmp	*tmp;
	t_texture_tmp	*next;

	tmp = texture;
	while (tmp)
	{
		next = tmp->next;
		while (next)
		{
			if (next->type == tmp->type)
				return (0);
			next = next->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

t_texture_tmp	*create_node(char **split)
{
	t_texture_tmp	*new_node;

	if (!split || !split[0] || !split[1])
		return (NULL);
	new_node = malloc(sizeof(t_texture_tmp));
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
		return (free(new_node), NULL);
	new_node->path = strdup_without_n(split[1]);
	new_node->next = NULL;
	return (new_node);
}

int	add_texture(t_texture_tmp **head, char **split)
{
	t_texture_tmp	*new_node;
	t_texture_tmp	*tmp;

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

int	skip_empty_lines(t_mapping *game, int *count, char **line)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	*line = get_next_line(game->fd);
	if (!*line)
		return (0);
	while (!ft_strncmp(*line, "\n", 1))
	{
		free(*line);
		*line = get_next_line(game->fd);
		if (!*line)
			return (0);
		(*count)++;
	}
	get_next_line(-1);
	return (1);
}

int	get_texture_and_map(t_mapping *game, char *filename)
{
	int		count;
	char	*line;
	char	**tmp;

	count = 0;
	while (1)
	{
		line = get_next_line(game->fd);
		count++;
		if (!line)
			break ;
		if (!ft_strncmp(line, "\n", 1))
		{
			free(line);
			continue ;
		}
		tmp = ft_split(line, ' ');
		if (!tmp || tmp[0][0] == '1')
			return (free_gnl_split_line(tmp, line), 0);
		if (!add_texture(&game->texture, tmp))
			return (free_gnl_split_line(tmp, line), 0);
		if (ft_lstlen(game->texture) == 6)
		{
			if (!skip_empty_lines(game, &count, &line) || !size_map(game,
					filename, count))
				return (free_gnl_split_line(tmp, line), 0);
			if (!check_double(game->texture) || !format_rgb(game->texture)
				|| !get_map(game, &line))
				return (free_gnl_split_line(tmp, line), 0);
			if (!map_parsing(game))
				return (free_gnl_split_line(tmp, line), 0);
			return (free_gnl_split_line(tmp, line), 1);
		}
		free_split(tmp);
		free(line);
	}
	get_next_line(-1);
	return (0);
}

