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

static int	scan_map(t_app *app, int player_count)
{
	int		x;
	int		y;
	char	c;

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

static char	**copy_and_padding_map(t_app *app)
{
	char	**copy;
	int		y;
	int		len;

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

static int	flood_fill(char **map, int x, int y, t_app *app)
{
	if (x < 0 || y < 0 || y >= app->map->height || x >= app->map->width)
		return (FAILURE);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (SUCCESS);
	if (map[y][x] == ' ')
		return (FAILURE);
	map[y][x] = 'V';
	if (flood_fill(map, x + 1, y, app) == FAILURE)
		return (FAILURE);
	if (flood_fill(map, x - 1, y, app) == FAILURE)
		return (FAILURE);
	if (flood_fill(map, x, y + 1, app) == FAILURE)
		return (FAILURE);
	if (flood_fill(map, x, y - 1, app) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	validate_map(t_app *app)
{
	char	**tempo_map;
	int		player_count;
	int		chk_enclosed_wall;

	if (!app->map->no_path || !app->map->so_path || !app->map->we_path || \
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
	chk_enclosed_wall = flood_fill(tempo_map, app->map->player_x, \
app->map->player_y, app);
	free_split(tempo_map);
	if (chk_enclosed_wall == FAILURE)
		return (error_msg(ERR_MAP_WALL), FAILURE);
	return (SUCCESS);
}
