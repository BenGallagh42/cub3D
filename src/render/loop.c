/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:00:41 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/14 15:59:46 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// This function runs ONCE per frame — draws everything!
void	render_frame(t_app *app)
{
	draw_background(app);
	update_movement(app);
	cast_all_rays(app);
}

// MLX42 calls this function 60+ times per second
void	loop_hook(void *param)
{
	t_app	*app;

	app = param;
	render_frame(app);
}
