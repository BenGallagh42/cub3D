/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:02:02 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/12 17:40:34 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// DDA loop: finds wall hit
void	perform_dda(t_app *app)
{
	t_ray	*r;

	r = app->ray;
	r->hit = 0;
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (app->map->grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

// Calculates perpendicular distance and wall height
void	calculate_wall_distance(t_app *app)
{
	t_ray	*r;

	r = app->ray;
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - app->player->pos_x
				+ (1 - r->step_x) / 2) / r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - app->player->pos_y
				+ (1 - r->step_y) / 2) / r->ray_dir_y;
	r->line_height = (int)(SCREEN_HEIGHT / r->perp_wall_dist);
	r->draw_start = (SCREEN_HEIGHT - r->line_height) / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->draw_start + r->line_height;
	if (r->draw_end >= SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
}

// Draws vertical wall stripe at column x
void	draw_wall_stripe(t_app *app, int x)
{
	t_ray		*r;
	uint32_t	*pixels;
	int			y;
	uint32_t	color;

	r = app->ray;
	pixels = (uint32_t *)app->screen->pixels;
	if (r->side == 0)
		color = 0xFF888888;
	else
		color = 0xFF666666;
	y = r->draw_start;
	while (y < r->draw_end)
	{
		pixels[y * SCREEN_WIDTH + x] = color;
		y++;
	}
}
