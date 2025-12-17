/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:16:12 by kkomasat          #+#    #+#             */
/*   Updated: 2025/12/17 16:23:50 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// catches lines with no map content (only spaces) by map line checking
static int	chk_at_least_one_map_character(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || \
line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

// Returns: 0 = OK, 1 = textures missing, 2 = colors missing
static int	chk_map_and_color_set(t_app *app)
{
	if (!app->map->no_path || !app->map->so_path || \
!app->map->we_path || !app->map->ea_path)
		return (1);
	if (!app->tex->floor_set || !app->tex->ceiling_set)
		return (2);
	return (0);
}

// Expands map grid to add a new row
static char	**expand_map_row(t_app *app, int *row)
{
	char	**new_grid;
	int		old_row;

	old_row = 0;
	if (app->map->grid)
	{
		while (app->map->grid[old_row])
			(old_row)++;
	}
	new_grid = (char **)ft_calloc(old_row + 2, sizeof(char *));
	if (!new_grid)
		return (NULL);
	*row = 0;
	if (app->map->grid)
	{
		while (*row < old_row)
		{
			new_grid[*row] = app->map->grid[*row];
			(*row)++;
		}
		free(app->map->grid);
	}
	return (new_grid);
}

// Adds one line to the map grid
static int	insert_map_row(t_app *app, char *line)
{
	char	**new_grid;
	size_t	len;
	int		row;

	row = 0;
	new_grid = expand_map_row(app, &row);
	if (!new_grid)
		return (error_msg(ERR_ALLOC), FAILURE);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	new_grid[row] = (char *)ft_calloc(len + 1, sizeof(char));
	if (!new_grid[row])
	{
		app->map->grid = new_grid;
		return (error_msg(ERR_ALLOC), FAILURE);
	}
	ft_memcpy(new_grid[row], line, len);
	new_grid[row][len] = '\0';
	new_grid[row + 1] = NULL;
	app->map->grid = new_grid;
	app->map->height++;
	return (SUCCESS);
}

// Parses map lines — checks order and valid characters
int	parse_map(t_app *app, char *line)
{
	int	check_status;

	check_status = chk_map_and_color_set(app);
	if (check_status == 1)
		return (error_msg(ERR_TEX_MISS), FAILURE);
	if (check_status == 2)
		return (error_msg(ERR_COLOR_MISS), FAILURE);
	if (app->map->grid && chk_empty_line(line))
		return (error_msg(ERR_MAP_GAP), FAILURE);
	if (!chk_at_least_one_map_character(line))
		return (error_msg(ERR_MAP_CHAR), FAILURE);
	if (!chk_invalid_character(line))
		return (error_msg(ERR_MAP_CHAR), FAILURE);
	return (insert_map_row(app, line));
}
