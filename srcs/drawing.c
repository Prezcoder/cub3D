/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:30:07 by fbouchar          #+#    #+#             */
/*   Updated: 2023/09/21 10:03:33 by fbouchar         ###   ########.fr       */
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
// int	direction(t_data *data)
// {
// 	if(data->angle <= 45 && data->angle >= 271);
// }


int	distance(int coor, int dir_coor)
{
	while(coor % MINITILES != 0)
		coor += dir_coor;
	return(coor);
}
// delta_x = x2 - x1

// # Calcul de la différence en y
// delta_y = delta_x * math.tan(angle_radians)

// # Calcul de y2
// y2 = y1 + delta_y

int	find_y(int x1, int y1, int x2, double angle)
{
	double del_x;
	double del_y;
	int y2;

	del_x = x2 - x1;
	del_y = del_x * tan(angle * DEGRE);
	y2 = y1 + del_y;
	return(y2);
}

int	find_x(int x1, int y1, int y2, double angle)
{
	double del_x;
	double del_y;
	int x2;

	del_y = y2 - y1;
	del_x = del_y / tan(angle * DEGRE);
	x2 = x1 + del_x;
	return(x2);
}

int		find_next_wall(int coor, int dir)
{
	while(coor % MINITILES != 0)
		coor += dir;
	return(coor);
}

void	calc_coor(t_coor *coor, double angle)
{
		int dist;
		
		dist = 1;
		double tile_s;
		tile_s = MINITILES;
		// (void) coor;
		
		while(dist < 10)
		{
			coor->x = coor->x + (dist * cos(angle * DEGRE));
			coor->y = coor->y + (dist * sin(angle * DEGRE));
			dist++;
		}
}

void	dda_algorithm(double x1, double y1, double angle, mlx_image_t *drawline)
{
	int	i;
	int	steps;
	double	dx;
	double	dy;
	double	xinc;
	double	yinc;
	int x2;
	int y2;
	x2 = 0;
	y2 = 0;
	// calc_coor(&end_coor, angle);
	i = 1;
	steps = 0;
	if(angle >  315 || angle <= 45)
	{
		x2 = find_next_wall(x1, -1);
		dx =  x2 - x1;		// dx = x2 - x1
		dy = find_y(x1, y1, x2, angle) - y1;		//dy = y2 - y1
	}
	if(angle >  135 && angle <= 225)
	{
		x2 = find_next_wall(x1, 1);
		dx =  x2 - x1;		// dx = x2 - x1
		dy = find_y(x1, y1, x2, angle) - y1;		//dy = y2 - y1
	}
	if(angle >  45 && angle <= 135)
	{
		y2 = find_next_wall(y1, -1);
		dx =  find_x(x1, y1, y2, angle) - x1;		// dx = x2 - x1
		dy =  y2 - y1;		//dy = y2 - y1
	}
	if(angle >  225 && angle <= 315)
	{
		y2 = find_next_wall(y1, 1);
		dx =  find_x(x1, y1, y2, angle) - x1;		// dx = x2 - x1
		dy =  y2 - y1;		//dy = y2 - y1
	}
	printf("X %d\n", x2);
	printf("ANGLE %f\n", angle);
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
		mlx_put_pixel(drawline, x1, y1, 0xFF0000FF);
		x1 = x1 + xinc;
		y1 = y1 + yinc;
	}
}
