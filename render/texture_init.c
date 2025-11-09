/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:53:36 by lenakach          #+#    #+#             */
/*   Updated: 2025/11/09 18:41:02 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_file_exist(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	parse_color(char *color_str)
{
	int	r;
	int	g;
	int	b;
	char	**split;
	int	color;

	split = ft_split(color_str, ',');
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	color = (r << 16) | (g << 8) | b;
	free_split(split);
	return (color);
}

t_img	*load_texture(void *mlx, char *path)
{
	t_img	*image;

	image = malloc(sizeof(t_img));
	if (!image)
		return (NULL);
	if (!check_file_exist(path))
		return (NULL);
	image->img = mlx_xpm_file_to_image(mlx, path, &image->width, &image->height);
	if (!image->img)
	{
		printf("ERREUR WITH IMAGE TEXTURE\n");
		free(image);
		return (NULL);
	}
	image->addr = mlx_get_data_addr(image->img, &image->bpp, &image->line_len, &image->endian);
	if (!image->addr)
	{
		printf("ERRREUR WITH ADD IMAGE\n");
		return (NULL);
	}
	return (image);
}

int	load_all_texture(t_window *game)
{
	t_texture_tmp	*current;

	game->texture = malloc(sizeof(t_texture));
	if (!game->texture)
		return (0);
	current = game->parsed_map->texture;
	while (current)
	{
		if (current->type == NO)
			game->texture->north = load_texture(game->mlx, current->path);
		else if (current->type == SO)
			game->texture->south = load_texture(game->mlx, current->path);
		else if (current->type == WE)
			game->texture->west = load_texture(game->mlx, current->path);
		else if (current->type == EA)
			game->texture->east = load_texture(game->mlx, current->path);
		else if (current->type == F)
			game->texture->floor = parse_color(current->path);
		else if (current->type == C)
			game->texture->ceiling = parse_color(current->path);
		current = current->next;
	}
	if (!game->texture->north || !game->texture->south || !game->texture->west || !game->texture->east)
		return (0);
	return (1);
}