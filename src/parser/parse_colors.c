/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:15:45 by kkomasat          #+#    #+#             */
/*   Updated: 2025/11/26 22:15:47 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int chk_color_identifier(char *line, int *i)
{
    skip_spaces(line, i);
    if (line[*i] == 'F' && (line[*i + 1] == ' ' || line[*i + 1] == '\t' || line[*i + 1] == '\n' || line[*i + 1] == '\0'))
        return (1);
    if (line[*i] == 'C' && (line[*i + 1] == ' ' || line[*i + 1] == '\t' || line[*i + 1] == '\n' || line[*i + 1] == '\0'))
        return (2);
    return (0);
}

/**
 * Check RGB format is valid: "R,G,B" with no spaces or empty values
 * Valid: "220,100,0"
 * Invalid: "220, ,0" or "220,,0" or ",220,0"
 */
static int chk_color_format(char *str)
{
    int i;
    int comma_count;
    int digit_count;

    i = 0;
    comma_count = 0;
    digit_count = 0;
    while (str[i] && str[i] != '\n')
    {
        if (ft_isdigit(str[i]))
            digit_count++;
        else if (str[i] == ',')
        {
            if (digit_count == 0)
                return (FAILURE);
            comma_count++;
            digit_count = 0;
        }
        else
            return (FAILURE);
        i++;
    }
    if (comma_count != 2 || digit_count == 0)
        return (FAILURE);
    return (SUCCESS);
}

static int chk_color_range(char *str)
{
    int i;
    int value;

    i = 0;
    if (!str || !str[0])
        return (-1);
    while (str[i] && str[i] != '\n')
    {
        if (!ft_isdigit(str[i]))
            return (-1);
        i++;
    }
    value = ft_atoi(str);
    if (value < 0 || value > 255)
        return (-1);
    return (value);
}

static int add_color(char *line, unsigned int *color, int *is_set)
{
    char **rgb;
    int r;
    int g;
    int b;

    if (*is_set)
        return (error_msg(ERR_COLOR_DUP), FAILURE);
    if (chk_color_format(line) == FAILURE)
        return (error_msg(ERR_COLOR_FORMAT), FAILURE);
    rgb = ft_split(line, ',');
    if (!rgb)
        return (error_msg(ERR_ALLOC), FAILURE);
    if (!rgb[0] || !rgb[1] || !rgb[2])
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

int parse_colors(t_app *app, char *line)
{
    int i;
    int identifier_code;

    i = 0;
    identifier_code = chk_color_identifier(line, &i);
    if (identifier_code == 0)
        return (SKIP);
    i++;
    skip_spaces(line, &i);
    if (!line[i] || line[i] == '\n')
        return (error_msg(ERR_COLOR_MISS), FAILURE);
    if (identifier_code == 1)
        return (add_color(line + i, &app->tex->floor, &app->tex->floor_set));
    else if (identifier_code == 2)
        return (add_color(line + i, &app->tex->ceiling, &app->tex->ceiling_set));
    return (SKIP);
}
