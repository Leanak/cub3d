/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:49:11 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/11 18:04:41 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	split_len(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

int	is_alldigit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	format_rgb(t_texture_tmp *texture)
{
	t_texture_tmp	*tmp;
	char	**split;
	int			i;

	tmp = texture;
	while (tmp)
	{
		if (tmp->type == 4 || tmp->type == 5)
		{
			i = 0;
			split = ft_split(tmp->path, ',');
			if (split_len(split) < 3)
				return (free_split(split), 0);
			while (split[i])
			{
				if (!is_alldigit(split[i]) || ft_atoi(split[i]) > 255)
					return (free_split(split), 0);
				i++;
			}
			free_split(split);
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
