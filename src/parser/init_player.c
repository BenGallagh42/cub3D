/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 22:49:50 by kkomasat          #+#    #+#             */
/*   Updated: 2025/12/07 22:49:53 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Direction vectors for raycasting:
**
** N (North): facing up    -> dir(0, -1)  plane(0.66, 0)
** S (South): facing down  -> dir(0, 1)   plane(-0.66, 0)
** E (East):  facing right -> dir(1, 0)   plane(0, 0.66)
** W (West):  facing left  -> dir(-1, 0)  plane(0, -0.66)
**
** The plane vector is perpendicular to direction and defines FOV.
** 0.66 gives approximately 66 degree FOV (similar to Wolfenstein 3D)
*/

static void set_direction_north(t_player *player)
{
    player->dir_x = 0;
    player->dir_y = -1;
    player->plane_x = 0.66;
    player->plane_y = 0;
}

static void set_direction_south(t_player *player)
{
    player->dir_x = 0;
    player->dir_y = 1;
    player->plane_x = -0.66;
    player->plane_y = 0;
}

static void set_direction_east(t_player *player)
{
    player->dir_x = 1;
    player->dir_y = 0;
    player->plane_x = 0;
    player->plane_y = 0.66;
}

static void set_direction_west(t_player *player)
{
    player->dir_x = -1;
    player->dir_y = 0;
    player->plane_x = 0;
    player->plane_y = -0.66;
}

/*
** Initialize player position and direction based on map data.
** Position is set to center of the tile (+ 0.5).
** Call this AFTER validate_map() has found player_x, player_y, player_dir.
*/
int init_player(t_app *app)
{
    t_player *player;

    player = (t_player *)ft_calloc(1, sizeof(t_player));
    if (!player)
        return (error_msg(ERR_ALLOC), FAILURE);

    // Set position to center of tile
    player->pos_x = (double)app->map->player_x + 0.5;
    player->pos_y = (double)app->map->player_y + 0.5;

    // Set direction based on spawn orientation
    if (app->map->player_dir == 'N')
        set_direction_north(player);
    else if (app->map->player_dir == 'S')
        set_direction_south(player);
    else if (app->map->player_dir == 'E')
        set_direction_east(player);
    else if (app->map->player_dir == 'W')
        set_direction_west(player);

    // Replace player character with floor in map
    app->map->grid[app->map->player_y][app->map->player_x] = '0';
    app->player = player;
    return (SUCCESS);
}
