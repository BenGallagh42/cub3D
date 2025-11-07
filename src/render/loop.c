/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:00:41 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/07 18:58:03 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// Renders one fram: background (later also renders walls)
void	render_frame(t_app *app)
{
	draw_background(app);
	// cast_all_rays(app);  // ← Next step
}

// MLX42 loop hook - called every frame
void	loop_hook(void *param)
{
	t_app	*app;

	app = param;
	render_frame(app);
}
