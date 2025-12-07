/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:16:12 by kkomasat          #+#    #+#             */
/*   Updated: 2025/12/07 23:57:15 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	chk_map(char *line)
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

static int	chk_map_and_color_set(t_app *app)
{
	if (!app->map->no_path || !app->map->so_path || !app->map->we_path || \
!app->map->ea_path)
		return (FALSE);
	if (!app->tex->floor_set || !app->tex->ceiling_set)
		return (FALSE);
	return (TRUE);
}

static char	**expand_map_row(t_app *app, int *row)
{
	char	**new_grid;

	if (app->map->grid)
	{
		while (app->map->grid[*row])
			(*row)++;
	}
	new_grid = (char **)ft_calloc(*row + 2, sizeof(char *));
	if (!new_grid)
		return (error_msg(ERR_ALLOC), NULL);
	*row = 0;
	if (app->map->grid)
	{
		while (app->map->grid[*row])
		{
			new_grid[*row] = app->map->grid[*row];
			(*row)++;
		}
		free(app->map->grid);
	}
	return (new_grid);
}

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
		free(new_grid);
		return (error_msg(ERR_ALLOC), FAILURE);
	}
	ft_memcpy(new_grid[row], line, len);
	new_grid[row][len] = '\0';
	new_grid[row + 1] = NULL;
	app->map->grid = new_grid;
	app->map->height++;
	return (SUCCESS);
}

int	parse_map(t_app *app, char *line)
{
	if (!chk_map_and_color_set(app))
		return (error_msg(ERR_MAP_ORDER), FAILURE);
	if (app->map->grid && chk_empty_line(line))
		return (error_msg(ERR_MAP_GAP), FAILURE);
	if (!chk_map(line))
		return (error_msg(ERR_MAP_CHAR), FAILURE);
	if (!chk_map_chars(line))
		return (error_msg(ERR_MAP_CHAR), FAILURE);
	return (insert_map_row(app, line));
}
