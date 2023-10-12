/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 08:54:03 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/12 10:58:47 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	create_windows(t_data *data)
{
	data->image.window = mlx_new_image(data->mlx, WINWIDTH, WINHEIGHT);
	mlx_image_to_window(data->mlx, data->image.window, 0, 0);
	data->image.minimap = mlx_new_image(data->mlx, WINWIDTH, WINHEIGHT);
	mlx_image_to_window(data->mlx, data->image.minimap, 0, 0);
}

void	track_window(t_data *data)
{
	int32_t	x;
	int32_t	y;

	x = 0;
	y = 0;
	mlx_get_window_pos(data->mlx, &x, &y);
	printf("X :%d\n", x);
	printf("Y :%d\n", y);
	if (data->param.w_pos_x != x || data->param.w_pos_y != y)
	{
		mlx_set_window_pos(data->mlx, data->param.w_pos_x, data->param.w_pos_y);
	}
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
}

void	fill_array(mlx_texture_t *texture, uint32_t **ar)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	i;

	i = 0;
	y = 0;
	while (y < texture->height - 1)
	{
		x = 0;
		while (x < texture->width)
		{
			ar[y][x] = ft_color((uint32_t)texture->pixels[i],
					(uint32_t)texture->pixels[i + 1],
					(uint32_t)texture->pixels[i + 2],
					(uint32_t)texture->pixels[i + 3]);
			i += 4;
			x++;
		}
		y++;
	}
}
