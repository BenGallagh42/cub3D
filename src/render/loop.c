/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:00:41 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/12 17:37:56 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Renders one frame
void	render_frame(t_app *app)
{
	draw_background(app);
	update_movement(app);
	cast_all_rays(app);
}

// MLX42 loop hook - called every frame
void	loop_hook(void *param)
{
	t_app	*app;

	app = param;
	render_frame(app);
}
