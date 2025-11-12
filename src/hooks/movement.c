/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:15:36 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/12 17:39:46 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Checks if position (x,y) is inside a wall
static int	is_wall(t_app *app, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= app->map->width
		|| map_y < 0 || map_y >= app->map->height)
		return (1);
	return (app->map->grid[map_y][map_x] == '1');
}

// Moves player forward or backward
static void	move_forward_backward(t_app *app)
{
	double	move_speed;

	move_speed = 0.1;
	if (mlx_is_key_down(app->mlx, MLX_KEY_W))
	{
		if (!is_wall(app, app->player->pos_x + app->player->dir_x * move_speed,
				app->player->pos_y))
			app->player->pos_x += app->player->dir_x * move_speed;
		if (!is_wall(app, app->player->pos_x,
				app->player->pos_y + app->player->dir_y * move_speed))
			app->player->pos_y += app->player->dir_y * move_speed;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_S))
	{
		if (!is_wall(app, app->player->pos_x - app->player->dir_x * move_speed,
				app->player->pos_y))
			app->player->pos_x -= app->player->dir_x * move_speed;
		if (!is_wall(app, app->player->pos_x,
				app->player->pos_y - app->player->dir_y * move_speed))
			app->player->pos_y -= app->player->dir_y * move_speed;
	}
}

// Updates player position and rotation
void	update_movement(t_app *app)
{
	move_forward_backward(app);
	rotate_left(app);
	rotate_right(app);
}
