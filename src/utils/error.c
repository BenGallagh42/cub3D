/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:24:25 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/07 18:58:56 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Prints error message to stderr and returns FAILURE
int error_msg(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (FAILURE);
}

void cleanup(t_app *app)
{
	if (app->tex)
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
	if (app->map)
	{
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

void fatal_error(const char *msg, t_app *app)
{
	error_msg(msg);
	cleanup(app);
	exit(FAILURE);
}
