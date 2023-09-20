/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:30:07 by fbouchar          #+#    #+#             */
/*   Updated: 2023/09/19 14:52:26 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// int	find_wall(int coor, int direction)
// {
// 	while((coor % MINITILES) != 0)
// 	{
// 		coor += direction;
// 	}
// 	return (coor);
// }

// void	find_end_p(int x, int y, double delta)
// {
// 	int dx;
// 	int dy;

// 	if(dx == 1)
// 	{
// 		x = find_wall(x, dx);
// 		if(data.map)
// 	}
// }

void	dda_algorithm(double x1, double y1, double x2, double y2, mlx_image_t *drawline)
{
	int	i;
	double	dx;
	double	dy;
	double	steps;
	double	xinc;
	double	yinc;

	i = 1;
	steps = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	xinc = dx / steps;
	yinc = dy / steps;
	while (i++ <= steps && x1 != 0 && y1 != 0)
	{
		mlx_put_pixel(drawline, x1, y1, 0xFF00FFFF);
		x1 = x1 + xinc;
		y1 = y1 + yinc;
	}
}

void	trouve_murx(t_data *data)
{
	int	x;
	int	y;
	
	data->ray.pos_x = 0.0;
	x = data->player.map_x;
	data->ray.pos_x = data->image.miniplayer->instances->x;
	y = data->player.map_y;
	while (data->map[y][x] != '1' && data->map[y][x])
	{
		x++;
		data->ray.pos_x += MINITILES;
	}
	data->ray.pos_y = y * MINITILES;
}
void	trouve_mury(t_data *data)
{
	int	x;
	int	y;

	data->ray.pos_y = 0.0;
	x = data->player.map_x;
	data->ray.pos_y = data->image.miniplayer->instances->y;
	y = data->player.map_y;
	while (data->map[y][x] != '1' && data->map[y][x])
	{
		y++;
		data->ray.pos_y += MINITILES;
	}
	data->ray.pos_x =  x * MINITILES;
}