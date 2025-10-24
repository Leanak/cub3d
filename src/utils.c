/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:11:36 by lenakach          #+#    #+#             */
/*   Updated: 2025/10/24 11:11:51 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_lstlen(t_texture *texture)
{
	t_texture	*tmp;
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
