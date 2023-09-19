/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:30:07 by fbouchar          #+#    #+#             */
/*   Updated: 2023/09/19 16:51:00 by emlamoth         ###   ########.fr       */
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

// int	find_end_p(t_data *data, int x, int y, double delta)
// {
// 	int dx;
// 	(void) delta;
// 	dx = 1;

// 	if(dx == 1)
// 	{
// 		x = find_wall(x, dx);
// 		if(data->map[y][x / MINITILES] == '1')
// 			return (x);
// 		else
// 			find_wall(x, dx);
// 	}
// 	return (0);
// }

void	calc_coor(t_coor *coor, int dist, int angle)
{
		(void) angle;
		(void) dist;
		// (void) coor;
		coor->x = coor->x + (dist * cos(angle * DEGRE));
		coor->y = coor->y + (dist * sin(angle * DEGRE));	
}

void	dda_algorithm(double x1, double y1, int angle, mlx_image_t *drawline)
{
	(void) angle;
	int	i;
	int	steps;
	double	dx;
	double	dy;
	double	xinc;
	double	yinc;
	t_coor end_coor;
	end_coor.x = (double)x1;
	end_coor.y = (double)y1;
	calc_coor(&end_coor, 50, angle);
	i = 1;
	steps = 0;
	dx = end_coor.x - x1;
	dy = end_coor.y - y1;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	xinc = dx / steps;
	yinc = dy / steps;
	while (i++ <= steps)
	{
		mlx_put_pixel(drawline, x1, y1, 0xFF00FFFF);
		x1 = x1 + xinc;
		y1 = y1 + yinc;
	}
}