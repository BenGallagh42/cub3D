/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:25:04 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/12 21:11:10 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Helper: loads PNG and converts to mlx_image_t
static mlx_image_t	*load_texture(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	tex = mlx_load_png(path);
	if (!tex)
		return (NULL);
	img = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	if (!img)
		return (NULL);
	return (img);
}

// Loads 4 PNG textures and converts them to images
int	load_textures(t_app *app)
{
	app->tex->north = load_texture(app->mlx, app->map->no_path);
	app->tex->south = load_texture(app->mlx, app->map->so_path);
	app->tex->west = load_texture(app->mlx, app->map->we_path);
	app->tex->east = load_texture(app->mlx, app->map->ea_path);

	if (!app->tex->north || !app->tex->south
		|| !app->tex->west || !app->tex->east)
	{
		return (error_msg("Failed to load texture\n"), FAILURE);
	}
	return (SUCCESS);
}
