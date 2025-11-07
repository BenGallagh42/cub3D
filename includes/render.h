/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:03:34 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/07 18:32:11 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

// RENDER FUNCTIONS
int		init_mlx(t_app *app);
void	render_frame(t_app *app);
void	draw_background(t_app *app);
void	cast_all_rays(t_app *app);
void	draw_wall_stripe(t_app *app, int x);

#endif