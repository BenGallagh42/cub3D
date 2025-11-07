/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:58:48 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/07 18:56:01 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// Draws floor and ceiling using parsed or test colors
void	draw_background(t_app *app)
{
	uint32_t	*pixels;
	uint32_t	y;
	uint32_t	x;
	uint32_t	half;
	uint32_t	color;

	pixels = (uint32_t *)app->screen->pixels;
	half = SCREEN_HEIGHT / 2;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		if (y < half)
			color = app->tex->ceiling;
		else
			color = app->tex->floor;
		while (x < SCREEN_WIDTH)
		{
			pixels[y * SCREEN_WIDTH + x] = color;
			x++;
		}
		y++;
	}
}
