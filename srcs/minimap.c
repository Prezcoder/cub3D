/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:03:50 by emlamoth          #+#    #+#             */
/*   Updated: 2023/10/12 10:09:26 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_pixel_square(mlx_image_t *image, t_coor pos,
			t_coor size, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			mlx_put_pixel(image, pos.x + x, pos.y + y, color);
			x++;
		}
		y++;
	}
}

void	logical_minimap(t_data *data, t_minimap *map, int x, int y)
{
	int	cam_x;
	int	cam_y;

	cam_x = (int)data->ray.pos.y - MINIWIDTH / 2;
	cam_y = (int)data->ray.pos.x - MINIHEIGHT / 2;
	if ((y + cam_y >= 0) && (y + cam_y < data->param.nbline)
		&& (x + cam_x >= 0) && (x + cam_x
			< (int)ft_strlen(data->map[y + cam_y])))
	{
		if (data->map[y + cam_y][x + cam_x] == '0')
			draw_pixel_square(data->image.minimap, (t_coor){(x * MINISIZE)
				+ map->pos_x, (y * MINISIZE) + map->pos_y}, (t_coor){MINISIZE,
				MINISIZE}, map->floor_color);
		else if (data->map[y + cam_y][x + cam_x] == '1')
			draw_pixel_square(data->image.minimap, (t_coor){(x * MINISIZE)
				+ map->pos_x, (y * MINISIZE) + map->pos_y}, (t_coor){MINISIZE,
				MINISIZE}, map->wall_color);
		else if (data->map[y + cam_y][x + cam_x] == '2' || data->map[y + cam_y][x + cam_x] == '3')
			draw_pixel_square(data->image.minimap, (t_coor){(x * MINISIZE)
				+ map->pos_x, (y * MINISIZE) + map->pos_y}, (t_coor){MINISIZE,
				MINISIZE}, map->door_color);
		draw_filled_circle(data->image.minimap, (t_coor){(int)(MINISIZE
				* MINIWIDTH / 2) + 10, (int)(MINISIZE * MINIHEIGHT / 2) + 10},
			MINISIZE / 4, data->minimap.player_color);
	}
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	cam_x;
	int	cam_y;

	draw_pixel_square(data->image.minimap, (t_coor){data->minimap.pos_x - 5,
		data->minimap.pos_y - 5}, (t_coor){MINISIZE * MINIWIDTH + 10, MINISIZE
		* MINIHEIGHT + 10}, data->minimap.background_color);
	cam_x = (int)data->ray.pos.y - MINIWIDTH / 2;
	cam_y = (int)data->ray.pos.x - MINIHEIGHT / 2;
	y = 0;
	while (y < MINIHEIGHT)
	{
		x = 0;
		while (x < MINIWIDTH)
		{
			logical_minimap(data, &data->minimap, x, y);
			x++;
		}
		y++;
	}
}

void	draw_filled_circle(mlx_image_t *image, t_coor center,
			int radius, uint32_t color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	x = center.x - radius;
	while (x <= center.x + radius)
	{
		y = center.y - radius;
		while (y <= center.y + radius)
		{
			dx = x - center.x;
			dy = y - center.y;
			if (dx * dx + dy * dy <= radius * radius)
				mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}
