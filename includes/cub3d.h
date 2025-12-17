/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:31:12 by kkomasat          #+#    #+#             */
/*   Updated: 2025/12/11 12:30:18 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../libft/inc/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

// CONSTANTS ///
# define FALSE 0
# define TRUE 1
# define SUCCESS 0
# define FAILURE 1
# define SKIP -1

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define FOV_D 60
# define FOV_R 1.0471975511963976 // = FOV * PI / 180
# define MOVE_SPEED 0.1
# define TURN_SPEED 0.08
# define MOUSE_SENS 0.002
# define TILE_SIZE 1.0
# define PI 3.14159265358979323846

// ERROR MESSAGES ///
# define ERR_ARGS "Error\nUsage: ./cub3D <map.cub>\n"
# define ERR_NOT_CUB "Error\nFile must have .cub extension\n"
# define ERR_EMPTY "Error\nEmpty File !!\n"
# define ERR_INCOMPLETE "Error\nIncomplete Input Textures\n"
# define ERR_FILE_OPEN "Error\nCannot open file\n"
# define ERR_ALLOC "Error\nMemory allocation failed\n"
# define ERR_MLX_INIT "Error\nMLX initialization failed\n"
# define ERR_WIN_CREATE "Error\nFailed to create window\n"
# define ERR_IMG_CREATE "Error\nFailed to create image\n"

// Texture errors
# define ERR_TEX_MISS "Error\nMissing texture path (NO/SO/WE/EA)\n"
# define ERR_TEX_DUP "Error\nDuplicate texture identifier\n"
# define ERR_TEX_PATH "Error\nInvalid texture path\n"
# define ERR_TEX_LOAD "Error\nFailed to load texture (check path)\n"
# define ERR_TEX_FORMAT "Error\nTexture must be .png or .xpm\n"

// Color errors
# define ERR_COLOR_MISS "Error\nMissing floor or ceiling color\n"
# define ERR_COLOR_DUP "Error\nDuplicate floor/ceiling color\n"
# define ERR_COLOR_RANGE "Error\nWrong RGB values\n"
# define ERR_COLOR_COUNT "Error\nRGB: Exactly 3 values required for color\n"

// Map errors
# define ERR_MAP_EMPTY "Error\nMap is empty\n"
# define ERR_MAP_MISS "Error\nNo map found in file\n"
# define ERR_MAP_ORDER "Error\nMap must be last in file\n"
# define ERR_MAP_CHAR "Error\nInvalid character in map\n"
# define ERR_MAP_WALL "Error\nMap not surrounded by walls\n"
# define ERR_MAP_PLAYER "Error\nExactly one player (N/S/E/W) required\n"
# define ERR_MAP_SPACE "Error\nSpace found inside map (use 1 or 0)\n"
# define ERR_MAP_GAP "Error\nEmpty line inside map\n"

// STRUCTURES ///
typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	char			player_dir;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
}	t_map;

typedef struct s_textures
{
	mlx_image_t		*north;
	mlx_image_t		*south;
	mlx_image_t		*west;
	mlx_image_t		*east;
	unsigned int	floor;
	unsigned int	ceiling;
	int				floor_set;
	int				ceiling_set;
}	t_textures;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}	t_player;

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
	double			tex_pos;
	double			tex_step;
}	t_ray;

typedef struct s_app
{
	mlx_t		*mlx;
	mlx_image_t	*screen;
	t_map		*map;
	t_player	*player;
	t_textures	*tex;
	t_ray		*ray;
}	t_app;

typedef struct s_point
{
	int			x;
	int			y;
}	t_point;

typedef struct s_stack
{
	t_point		*data;
	int			top;
	int			capacity;
}	t_stack;

// FUNCTIONS ///
// int parse_file(t_app *app, char *path);
int			load_textures(t_app *app);
int			init_mlx(t_app *app);
void		cleanup(t_app *app);

// PARSER FUNCTIONS ///
int			parser(t_app *app, char *argv);
int			parse_texture(t_app *app, char *line);
int			parse_colors(t_app *app, char *line);
int			parse_map(t_app *app, char *line);
int			validate_map(t_app *app);

// ADDITIONAL FUNC FOR PARSER
int			chk_empty_line(char *line);
int			chk_extention(char *filename, char *ext);
void		skip_spaces(char *line, int *i);
void		ft_trim_trailing(char *str);
void		cal_map_width(t_app *app);
int			chk_invalid_character(char *line);
int			init_player(t_app *app);
char		*ft_strncpy(char *dest, const char *src, size_t n);

// ADDITIONAL FUNC FOR ITERATIVE FLODDFILL
t_stack		*init_stack(int capacity);
void		free_stack(t_stack *stack);
int			stack_push(t_stack *stack, int x, int y);
int			stack_pop(t_stack *stack, int *x, int *y);
int			stack_is_empty(t_stack *stack);

// RENDER FUNCTIONS
// Init mlx + frame loop
int			init_mlx(t_app *app);
void		draw_background(t_app *app);
void		loop_hook(void *param);

// Raycasting functions
void		cast_all_rays(t_app *app);
void		perform_dda(t_app *app);
void		calculate_wall_distance(t_app *app);
void		draw_wall_stripe(t_app *app, int x);
mlx_image_t	*get_wall_texture(t_app *app);

// HOOKS FUNCTIONS
void		key_hook(mlx_key_data_t keydata, void *param);
void		update_movement(t_app *app);
void		rotate_left(t_app *app);
void		rotate_right(t_app *app);
void		handle_mouse_rotation(t_app *app);

// Utils
int			error_msg(const char *msg);
void		free_split(char **split);

#endif
