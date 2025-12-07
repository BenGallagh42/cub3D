/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:16:20 by kkomasat          #+#    #+#             */
/*   Updated: 2025/11/26 22:16:21 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char *ft_strncpy(char *dest, const char *src, size_t n)
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

static int add_texture(char **texture_path, char *tmp_path)
{
    int fd;

    if (*texture_path != NULL)
        return (free(tmp_path), error_msg(ERR_TEX_DUP), FAILURE);
    if (!chk_extention(tmp_path, ".png") && !chk_extention(tmp_path, ".xpm"))
        return (free(tmp_path), error_msg(ERR_TEX_FORMAT), FAILURE);
    fd = open(tmp_path, O_RDONLY);
    if (fd < 0)
        return (free(tmp_path), error_msg(ERR_TEX_PATH), FAILURE);
    close(fd);
    *texture_path = tmp_path;
    return (SUCCESS);
}

static char *extract_path(char *line)
{
    int i;
    int len;
    char *tmp;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    len = ft_strlen(line + i);
    tmp = (char *)ft_calloc(len + 1, sizeof(char));
    ft_strncpy(tmp, line + i, len);
    tmp[len] = '\0';
    return (tmp);
}

static int chk_texture(char *line, int *i)
{
    skip_spaces(line, i);
    if (ft_strlen(line + *i) < 2)
        return (0);
    if (line[*i] == 'N' && line[*i + 1] == 'O')
        return (1);
    if (line[*i] == 'S' && line[*i + 1] == 'O')
        return (2);
    if (line[*i] == 'W' && line[*i + 1] == 'E')
        return (3);
    if (line[*i] == 'E' && line[*i + 1] == 'A')
        return (4);
    return (0);
}

int parse_texture(t_app *app, char *line)
{
    int i;
    int identifier_code;
    char *path;

    i = 0;
    path = NULL;
    identifier_code = chk_texture(line, &i);
    if (identifier_code)
    {
        path = extract_path(line + i + 2);
        if (!path)
            return (error_msg(ERR_TEX_MISS), FAILURE);
        ft_trim_trailing(path);
        if (*path == '\0')
        {
            free(path);
            return (error_msg(ERR_TEX_MISS), FAILURE);
        }
        if (identifier_code == 1)
            return (add_texture(&app->map->no_path, path));
        else if (identifier_code == 2)
            return (add_texture(&app->map->so_path, path));
        else if (identifier_code == 3)
            return (add_texture(&app->map->we_path, path));
        else if (identifier_code == 4)
            return (add_texture(&app->map->ea_path, path));
        return (SUCCESS);
    }
    return (SKIP);
}