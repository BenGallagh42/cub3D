/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:59:34 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/12 17:37:51 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initializes MLX42: creates window and render image
int	init_mlx(t_app *app)
{
	app->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	if (!app->mlx)
		return (error_msg(ERR_MLX_INIT), FAILURE);
	app->screen = mlx_new_image(app->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!app->screen)
		return (error_msg(ERR_IMG_CREATE), FAILURE);
	if (mlx_image_to_window(app->mlx, app->screen, 0, 0) == -1)
		return (error_msg(ERR_IMG_CREATE), FAILURE);
	return (SUCCESS);
}
