/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:24:25 by bboulmie          #+#    #+#             */
/*   Updated: 2025/12/08 00:28:39 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_msg(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (FAILURE);
}

static void	free_texture_paths(t_map *map)
{
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);
}

static void	free_mlx_textures(t_app *app)
{
	if (app->tex->north)
		mlx_delete_image(app->mlx, app->tex->north);
	if (app->tex->south)
		mlx_delete_image(app->mlx, app->tex->south);
	if (app->tex->west)
		mlx_delete_image(app->mlx, app->tex->west);
	if (app->tex->east)
		mlx_delete_image(app->mlx, app->tex->east);
	free(app->tex);
}

void	cleanup(t_app *app)
{
	if (app->tex)
		free_mlx_textures(app);
	if (app->map)
	{
		free_texture_paths(app->map);
		free_split(app->map->grid);
		free(app->map);
	}
	if (app->player)
		free(app->player);
	if (app->ray)
		free(app->ray);
	if (app->screen)
		mlx_delete_image(app->mlx, app->screen);
	if (app->mlx)
		mlx_terminate(app->mlx);
}
