/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:30:07 by fbouchar          #+#    #+#             */
/*   Updated: 2023/09/20 13:43:05 by fbouchar         ###   ########.fr       */
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

void	dda_algorithm(double x1, double y1, double x2, double y2, t_data *data, mlx_image_t *drawline)
{
	int	i;
	double	dx;
	double	dy;
	double	dist;
	double	steps;
	double	xinc;
	double	yinc;

	i = 1;
	steps = 0;
	if (y2 > x2)
	{
		if (y2 > y1)
			dist = y2 - y1;
		else
			dist = y1 - y2;
	}
	if (x2 > y2)
	{
		if (x2 > x1)
			dist = x2 - x1;
		else
			dist = x1 - x2;
	}
	
	x2 = x2 + (dist * cos(data->angle * DEGRE));
	y2 = y2 + (dist * sin(data->angle * DEGRE));
	if (y2 > y1)
		dy = y2 - y1;
	else
		dy = y1 - y2;
	if (x2 > x1)
		dx = x2 - x1;
	else
		dx = x1 - x2;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	xinc = dx / steps;
	printf("%f", xinc);
	yinc = dy / steps;
	printf("%f", yinc);
	while (i++ <= steps && x1 != 0 && y1 != 0)
	{
		mlx_put_pixel(drawline, x1, y1, 0x000000FF);
		x1 = x1 + xinc;
		y1 = y1 + yinc;
	}
}

void	trouve_murx(t_data *data)
{
	int	x;
	int	y;
	
	printf("%d\n", data->angle);
	data->ray.pos_x = data->image.miniplayer->instances->x;
	data->ray.pos_y = data->image.miniplayer->instances->y;
	while (data->ray.pos_x < WINWIDTH && data->ray.pos_x > 0 && data->ray.pos_y > 0 && data->ray.pos_y < WINHEIGHT)
	{
		data->ray.pos_x = data->ray.pos_x  + cos(data->angle * DEGRE);
		data->ray.pos_y = data->ray.pos_y - sin(data->angle * DEGRE);
		// data->ray.pos_y--;
		if (data->map[(int)fabs(data->ray.pos_y / MINITILES)][(int)fabs(data->ray.pos_x / MINITILES)] == '1')
			break;
	}
	// data->ray.pos_y = y * MINITILES;
}
void	trouve_mury(t_data *data)
{
	int	x;
	int	y;

	x = data->image.miniplayer->instances->x / MINITILES;
	data->ray.pos_x = data->image.miniplayer->instances->x;
	y = data->image.miniplayer->instances->y / MINITILES;
	data->ray.pos_y = data->image.miniplayer->instances->y;
	while (WINWIDTH && WINHEIGHT > 0)
	{
		data->ray.pos_x--;
		data->ray.pos_y++;
		if (data->map[(int)fabs(data->ray.pos_y / MINITILES)][((int)fabs(data->ray.pos_x / MINITILES))] == '1')
			break;
	}
	// data->ray.pos_x =  x * MINITILES;
}