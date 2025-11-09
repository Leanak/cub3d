/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:34:11 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/05 14:08:04 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_elements(t_mapping *game)
{
	int	i;
	int	j;
	int	count;
	int	len;
	
	i = -1;
	count = 0;
	while (++i < game->lines)
	{
		j = -1;
		len = ft_strlen(game->map[i]);
		if (game->map[i][len - 1] == '\n')
			len--;
		while (++j < len)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W')
					count++;
		}
	}
	return (count);
}
