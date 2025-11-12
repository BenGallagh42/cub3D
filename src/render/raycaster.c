/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:29:19 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/12 17:38:01 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Sets ray direction based on screen column
static void	init_ray_direction(t_app *app, int x)
{
	t_ray	*r;
	double	camera_x;

	r = app->ray;
	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	r->ray_dir_x = app->player->dir_x + app->player->plane_x * camera_x;
	r->ray_dir_y = app->player->dir_y + app->player->plane_y * camera_x;
}

// Sets map position and delta distances
static void	init_dda_setup(t_app *app)
{
	t_ray	*r;

	r = app->ray;
	r->map_x = (int)app->player->pos_x;
	r->map_y = (int)app->player->pos_y;
	r->delta_dist_x = fabs(1 / r->ray_dir_x);
	r->delta_dist_y = fabs(1 / r->ray_dir_y);
}

// Sets step and initial side distances
static void	init_step_and_side(t_app *app)
{
	t_ray	*r;

	r = app->ray;
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (app->player->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - app->player->pos_x)
			* r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (app->player->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - app->player->pos_y)
			* r->delta_dist_y;
	}
}

// Casts one ray and draws wall
static void	cast_single_ray(t_app *app, int x)
{
	init_ray_direction(app, x);
	init_dda_setup(app);
	init_step_and_side(app);
	perform_dda(app);
	calculate_wall_distance(app);
	draw_wall_stripe(app, x);
}

// Casts rays for all screen columns
void	cast_all_rays(t_app *app)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		cast_single_ray(app, x);
		x++;
	}
}
