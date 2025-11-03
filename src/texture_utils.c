/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:49:11 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/03 15:14:32 by lenakach         ###   ########.fr       */
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

int	format_rgb(t_texture *texture)
{
	printf("FORMAT RGB\n");
	t_texture	*tmp;
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
	//free_split(split);
	return (1);
}