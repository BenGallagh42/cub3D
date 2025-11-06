/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:31:47 by bboulmie          #+#    #+#             */
/*   Updated: 2025/11/06 19:26:17 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Initialize all pointers
static void	init_app(t_app *app)
{
	app->mlx = NULL;
	app->screen = NULL;
	app->map = NULL;
	app->player = NULL;
	app->tex = NULL;
	app->ray = NULL;
}

// Clean up everything
void	cleanup(t_app *app)
{
	// Free textures
	if (app->tex)
	{
		if (app->tex->north)
			mlx_delete_image(app->mlx, app->tex->north);
		if (app->tex->south)
			mlx_delete_image(app->mlx, app->tex->south);
		if (app->tex->west)
			mlx_delete_image(app->mlx, app->tex->west);
		if (app->tex->east)
			mlx_delete_image(app->mlx, app->tex->east);
		free(app->tex);
	}
	// Free map data
	if (app->map)
	{
		free_split(app->map->grid);
		free(app->map);
	}
	// Free player and raycasting data
	if (app->player)
		free(app->player);
	if (app->ray)
		free(app->ray);
	if (app->screen)
		mlx_delete_image(app->mlx, app->screen);
	// Terminate MLX42
	if (app->mlx)
		mlx_terminate(app->mlx);
}

// Program main function
int32_t	main(int ac, char **av)
{
	t_app	app;

	// 1. Initialize everything with NULL for safety
	init_app(&app);
	// 2. Validate input
	if (ac != 2)
		return (error_msg(ERR_ARGS), FAILURE);
	// 3. Parse the .cub file
	if (parse_file(&app, av[1]) == FAILURE)
		return (cleanup(&app), FAILURE);
	// 4. Initialize MLX42 (create wondow, etc...)
	if (init_mlx(&app) == FAILURE)
		return (cleanup(&app), FAILURE);
	// 5. Load textures
	if (load_textures(&app) == FAILURE)
		return (cleanup(&app), FAILURE);
	// 6. Set up input hooks
	mlx_key_hook(app.mlx, key_hook, &app);
	mlx_loop_hook(app.mlx, loop_hook, &app);
	// 7. Start the main game loop
	mlx_loop(app.mlx);
	// 8. Clean exit (ESC or window close)
	cleanup(&app);
	return (SUCCESS);
}
