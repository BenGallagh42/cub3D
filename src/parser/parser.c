/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:15:52 by kkomasat          #+#    #+#             */
/*   Updated: 2025/12/09 20:49:30 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Parses one line: texture, color, or map — returns SUCCESS/FAILURE/SKIP
// Rules:
// Empty lines before map: OK
// Empty lines inside map: ERROR (gap)
// Empty lines after map: OK (trailing)
// Non-empty line after map ended: ERROR
static int parse_line_by_line(t_app *app, char *line, int *map_ended)
{
	int ret;

	if (*map_ended)
	{
		if (chk_empty_line(line))
			return (SUCCESS);
		return (error_msg(ERR_MAP_GAP), FAILURE);
	}
	if (app->map->grid && chk_empty_line(line))
	{
		*map_ended = 1;
		return (SUCCESS);
	}
	if (chk_empty_line(line))
		return (SUCCESS);
	ret = parse_texture(app, line);
	if (ret != SKIP)
		return (ret);
	ret = parse_colors(app, line);
	if (ret != SKIP)
		return (ret);
	ret = parse_map(app, line);
	if (ret != SKIP)
		return (ret);
	return (error_msg("Invalid line in .cub file\n"), FAILURE);
}

// Main parser: opens file, reads line by line, validates at end
int parser(t_app *app, char *argv)
{
	int fd;
	char *line;
	int result;
	int map_ended;

	map_ended = 0;
	if (!chk_extention(argv, ".cub"))
		return (error_msg(ERR_NOT_CUB), FAILURE);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (error_msg(ERR_FILE_OPEN), FAILURE);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), error_msg(ERR_MAP_EMPTY), FAILURE);
	while (line)
	{
		result = parse_line_by_line(app, line, &map_ended);
		free(line);
		if (result == FAILURE)
		{
			while ((line = get_next_line(fd)))
				free(line);
			close(fd);
			return (FAILURE);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (validate_map(app));
}
