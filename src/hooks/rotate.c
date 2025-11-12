/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:20:40 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/12 17:39:39 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Rotates player left
void	rotate_left(t_app *app)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.05;
	if (!mlx_is_key_down(app->mlx, MLX_KEY_A))
		return ;
	old_dir_x = app->player->dir_x;
	app->player->dir_x = app->player->dir_x * cos(rot_speed)
		- app->player->dir_y * sin(rot_speed);
	app->player->dir_y = old_dir_x * sin(rot_speed)
		+ app->player->dir_y * cos(rot_speed);
	old_plane_x = app->player->plane_x;
	app->player->plane_x = app->player->plane_x * cos(rot_speed)
		- app->player->plane_y * sin(rot_speed);
	app->player->plane_y = old_plane_x * sin(rot_speed)
		+ app->player->plane_y * cos(rot_speed);
}

// Rotates player right
void	rotate_right(t_app *app)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = -0.05;
	if (!mlx_is_key_down(app->mlx, MLX_KEY_D))
		return ;
	old_dir_x = app->player->dir_x;
	app->player->dir_x = app->player->dir_x * cos(rot_speed)
		- app->player->dir_y * sin(rot_speed);
	app->player->dir_y = old_dir_x * sin(rot_speed)
		+ app->player->dir_y * cos(rot_speed);
	old_plane_x = app->player->plane_x;
	app->player->plane_x = app->player->plane_x * cos(rot_speed)
		- app->player->plane_y * sin(rot_speed);
	app->player->plane_y = old_plane_x * sin(rot_speed)
		+ app->player->plane_y * cos(rot_speed);
}
