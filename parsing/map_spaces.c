/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:08:57 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/03 20:21:17 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_spaces(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 32)
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*delete_spaces(char *str)
{
	int	i;
	int	j;
	int	len;
	char	*new_str;
	
	i = 0;
	j = 0;
	len = count_spaces(str);
	new_str = malloc((len * sizeof(char)) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 32)
			i++;
		else
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	free(str);
	new_str[j] = '\0';
	return (new_str);
}

int change_spaces(char **old_map)
{
	int	i;

	i = 0;
	while (old_map[i])
	{
		old_map[i] = delete_spaces(old_map[i]);
		if (!old_map[i])
			return (0);
		i++;
	}
	return (1);
}
