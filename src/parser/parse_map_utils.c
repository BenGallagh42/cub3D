/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 21:26:42 by kkomasat          #+#    #+#             */
/*   Updated: 2025/12/11 11:35:46 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Copies string safely
char *ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

// Catches lines with invalid characters (Not 0,1,N,S,E,W,space).
int chk_invalid_character(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' &&
			line[i] != 'S' && line[i] != 'E' && line[i] != 'W' &&
			line[i] != ' ' && line[i] != '\t')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

// Calculates maximum width of map (for padding)
void cal_map_width(t_app *app)
{
	int row;
	int len;
	int max_width;

	max_width = 0;
	row = 0;
	while (app->map->grid[row])
	{
		len = ft_strlen(app->map->grid[row]);
		if (len > max_width)
			max_width = len;
		row++;
	}
	app->map->width = max_width;
}
