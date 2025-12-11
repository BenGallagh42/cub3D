/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:15:45 by kkomasat          #+#    #+#             */
/*   Updated: 2025/12/11 12:24:21 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Checks if line starts with F or C followed by space
static int	chk_color_identifier(char *line, int *i)
{
	skip_spaces(line, i);
	if (line[*i] == 'F' && (line[*i + 1] == ' ' || line[*i + 1] == '\t' || \
line[*i + 1] == '\n' || line[*i + 1] == '\0'))
		return (1);
	if (line[*i] == 'C' && (line[*i + 1] == ' ' || line[*i + 1] == '\t' || \
line[*i + 1] == '\n' || line[*i + 1] == '\0'))
		return (2);
	return (0);
}

// FIXED: strict RGB parsing: rejects "255a", "300"
static int	chk_color_range(const char *str)
{
	int	i;
	int	val;

	i = 0;
	val = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i] || !ft_isdigit(str[i]))
		return (-1);
	while (str[i] && ft_isdigit(str[i]))
	{
		if ((val > INT_MAX / 10) || (val < INT_MIN / 10))
			return (-1);
		val = val * 10 + (str[i] - '0');
		if (val > 255)
			return (-1);
		i++;
	}
	if (str[i] && !ft_isspace(str[i]) && str[i] != '\n' && str[i] != '\0')
		return (-1);
	return (val);
}

// Sets floor or ceiling color from "R,G,B" string
static int	add_color(char *line, unsigned int *color, int *is_set)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (*is_set)
		return (error_msg(ERR_COLOR_DUP), FAILURE);
	rgb = ft_split(line, ',');
	if (!rgb)
		return (error_msg(ERR_ALLOC), FAILURE);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), error_msg(ERR_COLOR_COUNT), FAILURE);
	r = chk_color_range(rgb[0]);
	g = chk_color_range(rgb[1]);
	b = chk_color_range(rgb[2]);
	free_split(rgb);
	if (r == -1 || g == -1 || b == -1)
		return (error_msg(ERR_COLOR_RANGE), FAILURE);
	*color = ((r << 24) | (g << 16) | (b << 8) | 255);
	*is_set = TRUE;
	return (SUCCESS);
}

// Parses F and C color lines
int	parse_colors(t_app *app, char *line)
{
	int	i;
	int	identifier_code;

	i = 0;
	identifier_code = chk_color_identifier(line, &i);
	if (identifier_code == 0)
		return (SKIP);
	i++;
	skip_spaces(line, &i);
	if (!line[i] || line[i] == '\n')
		return (error_msg(ERR_COLOR_MISS), FAILURE);
	if (identifier_code == 1)
		return (add_color(line + i, &app->tex->floor, \
&app->tex->floor_set));
	else if (identifier_code == 2)
		return (add_color(line + i, &app->tex->ceiling, \
&app->tex->ceiling_set));
	return (SKIP);
}
