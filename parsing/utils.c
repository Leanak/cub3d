/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:11:36 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/08 10:31:04 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error(char *str)
{
	while(*str)
		write(2, str++, 1);
}

int	ft_lstlen(t_texture_tmp *texture)
{
	t_texture_tmp	*tmp;
	int			len;

	len = 0;
	tmp = texture;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
