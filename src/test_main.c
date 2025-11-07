/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:14:02 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/07 18:37:05 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"

// Initialize all app pointers to NULL
static void	init_app(t_app *app)
{
	app->mlx = NULL;
	app->screen = NULL;
	app->map = NULL;
	app->player = NULL;
	app->tex = NULL;
	app->ray = NULL;
}

// Free everything safely
void	cleanup(t_app *app)
{
	if (app->tex)
	{
		free(app->tex);
	}
	if (app->map)
	{
		free_split(app->map->grid);
		free(app->map);
	}
	if (app->player)
		free(app->player);
	if (app->ray)
		free(app->ray);
	if (app->screen)
		mlx_delete_image(app->mlx, app->screen);
	if (app->mlx)
		mlx_terminate(app->mlx);
}

// Hard-coded test data
static void	init_test_data(t_app *app)
{
	// --- Textures (dummy) ---
	app->tex = malloc(sizeof(t_textures));
	if (!app->tex)
		return ;
	app->tex->north = NULL;
	app->tex->south = NULL;
	app->tex->west = NULL;
	app->tex->east = NULL;
	app->tex->floor = 0xFF0000FF;   // Red
	app->tex->ceiling = 0xFFFF0000; // Blue

	// --- Player ---
	app->player = malloc(sizeof(t_player));
	if (!app->player)
		return ;
	app->player->pos_x = 5.5;
	app->player->pos_y = 5.5;
	app->player->dir_x = -1.0;
	app->player->dir_y = 0.0;
	app->player->plane_x = 0.0;
	app->player->plane_y = 0.66;    // FOV/2 tan

	// --- Ray ---
	app->ray = malloc(sizeof(t_ray));
	if (!app->ray)
		return ;

	// --- Map ---
	init_test_map(app);
}

// Main entry point — TEST MODE (no parser)
int32_t	main(void)
{
	t_app	app;

	init_app(&app);

	// 1. Initialize test data (map, colors, player)
	init_test_data(&app);
	if (!app.map || !app.player || !app.tex)
		return (error_msg(ERR_ALLOC), cleanup(&app), FAILURE);

	// 2. Initialize MLX42
	if (init_mlx(&app) == FAILURE)
		return (cleanup(&app), FAILURE);

	// 3. Set up hooks
	mlx_key_hook(app.mlx, key_hook, &app);
	mlx_loop_hook(app.mlx, loop_hook, &app);

	// 4. Start render loop
	mlx_loop(app.mlx);

	// 5. Clean exit
	cleanup(&app);
	return (SUCCESS);
}