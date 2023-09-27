/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:00:29 by emlamoth          #+#    #+#             */
/*   Updated: 2023/09/27 13:32:44 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//----------define
# define WINWIDTH 1024
# define WINHEIGHT 768
# define MINITILES 8
# define DEGRE M_PI / 180.0
# define MOVESPEED 5
# define MOVE_SPEED 0.00003
# define ROTATE_SPEED 0.000015

////////////----------error message
# define ERRARGC "Usage : ./cub3D <map.cub>\n"
# define ERRMAP	 "Invalid map file\n"
# define ERRIMG "Invalid image\n"
# define ERRCOLOR "Invalid color\n"
# define ERRPARSE "Informations are missing\n"
# define ERRPLAYER "Too many players\n"
# define ERRNOPLAYER "No player detected\n"
# define ERRCHAR "Wrong chars detected\n"


////////////----------temp
# define TEMPMAP "./graphics/bellebriquewow.png"
# define TEMPCOLOR "220,100,0"

//----------include
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "../srcs/libft/libft.h"
# include "../srcs/MLX42/include/MLX42/MLX42.h"

//----------struct

typedef struct s_player
{
	int				pos_x;
	int				pos_y;
	int				map_x;
	int				map_y;
	float			angle;
	int				start_map;
}			t_player;

typedef	struct s_vect
{
	double 			x;
	double 			y;
}	t_vect;

typedef struct s_ray {
	t_vect			pos;
	t_vect			dir;
	t_vect			plane;
	double			cam_x;
	t_vect			ray_dir;
	t_vect			coord;
	t_vect			side_dist;
	t_vect			delta_dist;
	t_vect			step;
	int				side;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
}	t_ray;

typedef struct s_param
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	uint32_t		ceil;
	uint32_t		floor;
	int				flgfloor;
	int				flgceil;
	int				nbline;
}			t_param;

typedef struct s_image
{
	
	mlx_image_t		*window;
	mlx_image_t		*minimap;
}			t_image;

typedef struct s_texture
{
	mlx_texture_t	*nord;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*ceil;
	mlx_texture_t	*floor;
}			t_texture;


typedef struct s_data
{
	mlx_t			*mlx;
	t_param			param;
	t_texture		texture;
	t_image			image;
	t_player		player;
	t_ray			ray;
	double			angle;
	char			**map;
	
}			t_data;

int			errhandler(char *msg);
void		parsing(t_data *data);
void		wall_check(t_data *data);

//----------init.c
t_data		*init_data(t_data *data, char **argv);
int			init_map(t_data *data, char *path);

uint32_t	ft_color(int32_t r, int32_t g, int32_t b, int32_t a);

void		ft_hook(void *param);
void		loop(void *param);
void		init_game(t_data *data);

#endif