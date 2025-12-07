/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:15:52 by kkomasat          #+#    #+#             */
/*   Updated: 2025/12/07 23:35:06 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_line_by_line(t_app *app, char *line)
{
	int	ret;

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
	return (error_msg("out of scope\n"), FAILURE);
}

int	parser(t_app *app, char *argv)
{
	int		fd;
	char	*line;
	int		result;

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
		result = parse_line_by_line(app, line);
		free(line);
		if (result == FAILURE)
		{
			close(fd);
			return (FAILURE);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (validate_map(app));
}
