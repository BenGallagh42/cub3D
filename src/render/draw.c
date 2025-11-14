/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:58:48 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/14 16:57:02 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Paints top half of screen ceiling color, bottom half floor color
void	draw_background(t_app *app)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	half;

	half = SCREEN_HEIGHT / 2;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		if (y < half)
			while (x < SCREEN_WIDTH)
				mlx_put_pixel(app->screen, x++, y, app->tex->ceiling);
		else
			while (x < SCREEN_WIDTH)
				mlx_put_pixel(app->screen, x++, y, app->tex->floor);
		y++;
	}
}

// Returns correct wall texture: East/West (vertical), North/South (horizontal)
mlx_image_t	*get_wall_texture(t_app *app)
{
	t_ray	*r;

	r = app->ray;
	if (r->side == 0)
	{
		if (r->step_x > 0)
			return (app->tex->east);
		return (app->tex->west);
	}
	if (r->step_y > 0)
		return (app->tex->south);
	return (app->tex->north);
}

// Samples 1 texture byte, assembles RGBA, draws pixel (no shading)
static void	draw_texture_pixel(t_app *app, int x, int y, mlx_image_t *tex)
{
	int		tex_y;
	int		tex_idx;
	t_ray	*r;
	uint8_t	*pixels;

	r = app->ray;
	tex_y = (int)r->tex_pos & (tex->height - 1);
	r->tex_pos += r->tex_step;
	tex_idx = tex_y * tex->width + r->tex_x;
	pixels = tex->pixels;
	mlx_put_pixel(app->screen, x, y,
		(pixels[tex_idx * 4 + 0] << 24) | (pixels[tex_idx * 4 + 1] << 16)
		| (pixels[tex_idx * 4 + 2] << 8) | (pixels[tex_idx * 4 + 3]));
}

// Draws 1 vertical wall stripe (column x) using texture
void	draw_wall_stripe(t_app *app, int x)
{
	t_ray		*r;
	mlx_image_t	*tex;
	int			y;

	r = app->ray;
	tex = get_wall_texture(app);
	y = r->draw_start;
	while (y < r->draw_end)
	{
		draw_texture_pixel(app, x, y, tex);
		y++;
	}
}
