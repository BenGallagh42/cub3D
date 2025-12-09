/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:20:40 by bboulmie          #+#    #+#             */
/*   Updated: 2025/12/09 20:57:34 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Rotates player view left or right
static void	apply_rotation(t_app *app, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = app->player->dir_x;
	old_plane_x = app->player->plane_x;
	app->player->dir_x = old_dir_x * cos(rot_speed)
		- app->player->dir_y * sin(rot_speed);
	app->player->dir_y = old_dir_x * sin(rot_speed)
		+ app->player->dir_y * cos(rot_speed);
	app->player->plane_x = old_plane_x * cos(rot_speed)
		- app->player->plane_y * sin(rot_speed);
	app->player->plane_y = old_plane_x * sin(rot_speed)
		+ app->player->plane_y * cos(rot_speed);
}

// Turn left when A or Left Arrow is pressed
void	rotate_left(t_app *app)
{
	if (!mlx_is_key_down(app->mlx, MLX_KEY_A)
		&& !mlx_is_key_down(app->mlx, MLX_KEY_LEFT))
		return ;
	apply_rotation(app, -TURN_SPEED);
}

// Turn right when D or Right Arrow is pressed
void	rotate_right(t_app *app)
{
	if (!mlx_is_key_down(app->mlx, MLX_KEY_D)
		&& !mlx_is_key_down(app->mlx, MLX_KEY_RIGHT))
		return ;
	apply_rotation(app, TURN_SPEED);
}

// Gets how far the mouse moved from screen center
static double	get_mouse_rotation(t_app *app, int32_t *center_x)
{
	int32_t	mouse_x;
	int32_t	mouse_y;
	double	delta_x;

	mlx_get_mouse_pos(app->mlx, &mouse_x, &mouse_y);
	*center_x = SCREEN_WIDTH / 2;
	delta_x = mouse_x - *center_x;
	return (delta_x);
}

// Turn left/right when mouse moves
void	handle_mouse_rotation(t_app *app)
{
	static int	first_call;
	int32_t		center_x;
	double		delta_x;
	double		rot_speed;

	first_call = 1;
	delta_x = get_mouse_rotation(app, &center_x);
	if (first_call)
	{
		mlx_set_mouse_pos(app->mlx, center_x, SCREEN_HEIGHT / 2);
		first_call = 0;
		return ;
	}
	if (fabs(delta_x) < 2)
		return ;
	rot_speed = delta_x * MOUSE_SENS;
	apply_rotation(app, rot_speed);
	mlx_set_mouse_pos(app->mlx, center_x, SCREEN_HEIGHT / 2);
}
