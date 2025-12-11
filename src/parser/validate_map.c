/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:16:30 by kkomasat          #+#    #+#             */
/*   Updated: 2025/12/08 00:10:39 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Scans map to count players and store position
static int scan_map(t_app *app, int player_count)
{
	int x;
	int y;
	char c;

	y = 0;
	while (app->map->grid[y])
	{
		x = 0;
		while (app->map->grid[y][x])
		{
			c = app->map->grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				app->map->player_x = x;
				app->map->player_y = y;
				app->map->player_dir = c;
				player_count++;
			}
			x++;
		}
		y++;
	}
	return (player_count);
}

// Creates padded copy of map for flood fill
static char **copy_and_padding_map(t_app *app)
{
	char **copy;
	int y;
	int len;

	copy = (char **)ft_calloc(app->map->height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < app->map->height)
	{
		copy[y] = (char *)ft_calloc(app->map->width + 1, sizeof(char));
		if (!copy[y])
		{
			while (--y >= 0)
				free(copy[y]);
			return (free(copy), NULL);
		}
		ft_memset(copy[y], ' ', app->map->width);
		len = ft_strlen(app->map->grid[y]);
		ft_memcpy(copy[y], app->map->grid[y], len);
		y++;
	}
	return (copy);
}

// -1 = out of bounds or space (map not closed - FAILURE)
//  0 = wall or already visited (skip)
//  1 = valid cell to visit
static int check_cell(char **map, int x, int y, t_app *app)
{
	if (x < 0 || y < 0 || y >= app->map->height || x >= app->map->width)
		return (-1);
	if (map[y][x] == ' ')
		return (-1);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	return (1);
}
// Iterative flood fill to check map is closed
static int flood_fill_iterative(char **map, int start_x, int start_y, t_app *app)
{
	t_stack *stack;
	int x;
	int y;
	int check;

	stack = init_stack(app->map->width * app->map->height);
	if (!stack)
		return (FAILURE);
	if (!stack_push(stack, start_x, start_y))
		return (free_stack(stack), FAILURE);
	while (!stack_is_empty(stack))
	{
		stack_pop(stack, &x, &y);
		check = check_cell(map, x, y, app);
		if (check == -1)
			return (free_stack(stack), FAILURE);
		if (check == 0)
			continue;
		map[y][x] = 'V';
		if (!stack_push(stack, x + 1, y) || !stack_push(stack, x - 1, y) ||
			!stack_push(stack, x, y + 1) || !stack_push(stack, x, y - 1))
			return (free_stack(stack), FAILURE);
	}
	return (free_stack(stack), SUCCESS);
}

// Validates entire map: textures, colors, player, closed walls
int validate_map(t_app *app)
{
	char **tempo_map;
	int player_count;
	int chk_enclosed_wall;

	if (!app->map->no_path || !app->map->so_path || !app->map->we_path ||
		!app->map->ea_path)
		return (error_msg(ERR_TEX_MISS), FAILURE);
	if (!app->tex->floor_set || !app->tex->ceiling_set)
		return (error_msg(ERR_COLOR_MISS), FAILURE);
	if (!app->map->grid || !app->map->grid[0])
		return (error_msg(ERR_MAP_MISS), FAILURE);
	cal_map_width(app);
	player_count = scan_map(app, 0);
	if (player_count != 1)
		return (error_msg(ERR_MAP_PLAYER), FAILURE);
	tempo_map = copy_and_padding_map(app);
	if (!tempo_map)
		return (error_msg(ERR_ALLOC), FAILURE);
	chk_enclosed_wall = flood_fill_iterative(tempo_map, app->map->player_x,
											 app->map->player_y, app);
	free_split(tempo_map);
	if (chk_enclosed_wall == FAILURE)
		return (error_msg(ERR_MAP_WALL), FAILURE);
	return (SUCCESS);
}
