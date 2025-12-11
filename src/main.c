/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:31:47 by bboulmie          #+#    #+#             */
/*   Updated: 2025/12/11 12:40:28 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->grid = NULL;
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	map->width = 0;
	map->height = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = -1;
	return (map);
}

static t_textures	*init_tex(void)
{
	t_textures	*tex;

	tex = (t_textures *)ft_calloc(1, sizeof(t_textures));
	if (!tex)
		return (NULL);
	tex->north = NULL;
	tex->south = NULL;
	tex->west = NULL;
	tex->east = NULL;
	tex->floor = 0;
	tex->ceiling = 0;
	tex->floor_set = FALSE;
	tex->ceiling_set = FALSE;
	return (tex);
}

static int	init_app(t_app *app)
{
	app->mlx = NULL;
	app->screen = NULL;
	app->map = init_map();
	if (!app->map)
		return (error_msg(ERR_ALLOC), FAILURE);
	app->player = NULL;
	app->tex = init_tex();
	if (!app->tex)
		return (error_msg(ERR_ALLOC), FAILURE);
	app->ray = malloc(sizeof(t_ray));
	if (!app->ray)
		return (error_msg(ERR_ALLOC), FAILURE);
	return (SUCCESS);
}

int32_t	main(int ac, char **av)
{
	t_app	app;

	if (ac != 2)
		return (error_msg(ERR_ARGS), FAILURE);
	if (init_app(&app) == FAILURE)
		return (cleanup(&app), FAILURE);
	if (parser(&app, av[1]) == FAILURE)
		return (cleanup(&app), FAILURE);
	if (init_mlx(&app) == FAILURE)
		return (cleanup(&app), FAILURE);
	if (init_player(&app) == FAILURE)
		return (cleanup(&app), FAILURE);
	if (load_textures(&app) == FAILURE)
		return (cleanup(&app), FAILURE);
	mlx_set_cursor_mode(app.mlx, MLX_MOUSE_HIDDEN);
	mlx_key_hook(app.mlx, key_hook, &app);
	mlx_loop_hook(app.mlx, loop_hook, &app);
	mlx_loop(app.mlx);
	cleanup(&app);
	return (SUCCESS);
}
