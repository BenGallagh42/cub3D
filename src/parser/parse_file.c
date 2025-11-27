/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:15:52 by kkomasat          #+#    #+#             */
/*   Updated: 2025/11/26 22:15:53 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
    parse_file(filename, data)
        ↓
    1. Check .cub extension
        ↓
    2. Open file
        ↓
    3. Initialize data structure
        ↓
    4. Read line by line with get_next_line()
        ↓
    5. For each line:
        - Empty line? → Skip
        - Texture line (NO/SO/WE/EA)? → parse_texture()
        - Color line (F/C)? → parse_color()
        - Map line (0/1/N/S/E/W)? → parse_map()
        ↓
    6. Validate complete map
        ↓
    7. Return success/failure
*/

int chk_extention(char argv[])
{
    int fd;
    char *ext;

    fd = open(argv, O_RDONLY);
    if (fd == -1)
        return (error_msg(ERR_FILE_OPEN), FAILURE);
    ext = ft_strrchr(argv, '.');
    if (ext[0] == '.' && ext[1] == 'c' && ext[2] == 'u' && ext[3] == 'b')
        return (SUCCESS);
    return (error_msg(ERR_NOT_CUB), FAILURE);
}

int parse_file(t_app *app, char *argv)
{
    (void)app;
    int fd;

    if (chk_extention(argv) == FAILURE)
        return (FAILURE);
    fd = open(argv, O_RDONLY);
    if (fd < 0)
        return (error_msg(ERR_FILE_OPEN), FAILURE);

    printf("completed\n");
    return (0);
}