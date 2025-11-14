/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:02:02 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/14 16:57:54 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// DDA: steps through map grid until hitting wall '1'
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

// Computes wall height on screen and draw start/end Y coords
static void	init_line_height(t_ray *r)
{
	r->line_height = (int)(SCREEN_HEIGHT / r->perp_wall_dist);
	r->draw_start = -(r->line_height / 2) + SCREEN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_end >= SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
}

// Computes exact hit position on wall (0.0-1.0) for texture X coord
static void	init_tex_x(t_app *app, mlx_image_t *tex)
{
	t_ray	*r;

	r = app->ray;
	if (r->side == 0)
		r->wall_x = app->player->pos_y + r->perp_wall_dist * r->ray_dir_y;
	else
		r->wall_x = app->player->pos_x + r->perp_wall_dist * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)tex->width);
	if ((r->side == 0 && r->ray_dir_x > 0)
		|| (r->side == 1 && r->ray_dir_y < 0))
		r->tex_x = tex->width - r->tex_x - 1;
}

// Computes vertical step in texture per screen pixel + start position
static void	init_tex_step(t_ray *r, mlx_image_t *tex)
{
	r->tex_step = (double)tex->height / (double)r->line_height;
	r->tex_pos = (r->draw_start - SCREEN_HEIGHT / 2.0 + r->line_height / 2.0)
		* r->tex_step;
}

// Calculates perpendicular wall distance + texture mapping setup
void	calculate_wall_distance(t_app *app)
{
	t_ray		*r;
	mlx_image_t	*tex;

	r = app->ray;
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - app->player->pos_x
				+ (1.0 - r->step_x) / 2.0) / r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - app->player->pos_y
				+ (1.0 - r->step_y) / 2.0) / r->ray_dir_y;
	tex = get_wall_texture(app);
	init_line_height(r);
	init_tex_x(app, tex);
	init_tex_step(r, tex);
}
