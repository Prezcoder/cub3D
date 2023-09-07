/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:00:29 by emlamoth          #+#    #+#             */
/*   Updated: 2023/09/07 16:49:41 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//----------define
# define WINWIDTH 2048
# define WINHEIGHT 1280

////////////----------error message
#define ERRARGC "Usage : ./cub3D <map.cub>\n"

////////////----------temp
# define TEMPMAP "./graphics/bellebriquewow.png"

//----------include
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../srcs/libft/libft.h"
# include "../srcs/MLX42/include/MLX42/MLX42.h"

//----------struct
typedef struct s_flood
{
	char			**map;
	int				collect;
	int				exit;
	int				done;
}			t_flood;

typedef struct s_player
{
	int				pos_x;
	int				pos_y;
}			t_player;

typedef struct s_base_param
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	char			*cell;
	char			*floor;
}			t_base_param;

typedef struct s_image
{
	mlx_image_t		*north;
	mlx_image_t		*south;
	mlx_image_t		*east;
	mlx_image_t		*west;
	mlx_image_t		*cell;
	mlx_image_t		*floor;
}			t_image;

typedef struct s_texture
{
	mlx_texture_t	*nord;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*cell;
	mlx_texture_t	*floor;
}			t_texture;

typedef struct s_data
{
	mlx_t			*mlx;
	t_base_param	visual;
	t_texture		texture;
	t_image			image;
	t_image			old_image;
	char			**map;
}			t_data;

#endif