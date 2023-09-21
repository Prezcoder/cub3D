/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:30:07 by fbouchar          #+#    #+#             */
/*   Updated: 2023/09/21 13:15:01 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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


// delta_x = x2 - x1

// # Calcul de la différence en y
// delta_y = delta_x * math.tan(angle_radians)

// # Calcul de y2
// y2 = y1 + delta_y

double	find_y(int x1, int y1, int x2, double angle)
{
	double del_x;
	double del_y;
	int y2;

	del_x = x2 - x1;
	del_y = del_x * tan(angle * DEGRE);
	y2 = y1 + del_y;
	return(y2);
}

double	find_x(int x1, int y1, int y2, double angle)
{
	double del_x;
	double del_y;
	int x2;

	del_y = y2 - y1;
	del_x = del_y / tan(angle * DEGRE);
	x2 = x1 + del_x;
	return(x2);
}

double		find_next_wall(int coor, int dir)
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
int	is_wall(t_data *data, double y, double x)
{
	int z;
	int u;

	printf("Y %f\n", y);
	printf("X %f\n", x);
	z = (int)fabs(y / MINITILES);
	u = (int)fabs(x / MINITILES);
	printf("Z %d\n", z);
	printf("U %d\n", u);
	printf("ICI :%c\n", data->map[z][u]);
	if(data->map[z][u] == '1')
	{
		ft_printf("test\n");
		return (1);
	}			
	return (0);
}

void calc_ray_x(t_data *data, t_ray *ray_x)
{	
	if(data->angle >  0 && data->angle <= 180)
	{
		ray_x->y2 = find_next_wall(ray_x->y1, -1);
		ray_x->x2 = find_x(ray_x->x1, ray_x->y1, ray_x->y2, data->angle);
		ray_x->dx = ray_x->x2 - ray_x->x1;		// dx = x2 - x1
		ray_x->dy = ray_x->y2 - ray_x->y1;		//dy = y2 - y1
		// while(ray_x->y2 <= WINHEIGHT && ray_x->y2 >= 0 && ray_x->x2 <= WINWIDTH && ray_x->x2 >= 0)
		// {
		// 	if(is_wall(data, ray_x->y2, ray_x->x2))
		// 		return ;
		// 	else
		// 	{
		// 		ray_x->y2 = find_next_wall(ray_x->y2 - 1, -1);
		// 		ray_x->x2 = find_x(ray_x->x1, ray_x->y1, ray_x->y2, data->angle);
		// 		ray_x->dx = ray_x->x2 - ray_x->x1;		// dx = x2 - x1
		// 		ray_x->dy = ray_x->y2 - ray_x->y1;
		// 	}			//dy = y2 - y1
		// }
	}
	if(data->angle > 180 && data->angle <= 360)
	{
		ray_x->y2 = find_next_wall(ray_x->y1, 1);
		ray_x->x2 = find_x(ray_x->x1, ray_x->y1, ray_x->y2, data->angle);
		ray_x->dx = ray_x->x2 - ray_x->x1;		// dx = x2 - x1
		ray_x->dy = ray_x->y2 - ray_x->y1;		//dy = y2 - y1
		// while(ray_x->y2 <= WINHEIGHT && ray_x->y2 >= 0 && ray_x->x2 <= WINWIDTH && ray_x->x2 >= 0)
		// {
		// 	if(is_wall(data, ray_x->y2, ray_x->x2))
		// 		return ;
		// 	else
		// 	{
		// 		ray_x->y2 = find_next_wall(ray_x->y2 + 1, 1);
		// 		ray_x->x2 = find_x(ray_x->x1, ray_x->y1, ray_x->y2, data->angle);
		// 		ray_x->dx = ray_x->x2 - ray_x->x1;		// dx = x2 - x1
		// 		ray_x->dy = ray_x->y2 - ray_x->y1;
		// 	}			//dy = y2 - y1
		// }
	}
	if (fabs(ray_x->dx) > fabs(ray_x->dy))
		ray_x->steps = fabs(ray_x->dx);
	else
		ray_x->steps = fabs(ray_x->dy);
}

void	calc_ray_y(t_data *data, t_ray *ray_y)
{
	if(data->angle >  270 || data->angle <= 90)
	{
		ray_y->x2 = find_next_wall(ray_y->x1, -1);
		ray_y->dx = ray_y->x2 - ray_y->x1;
		ray_y->y2 = find_y(ray_y->x1, ray_y->y1, ray_y->x2, data->angle);// dx = x2 - x1
		ray_y->dy = ray_y->y2 - ray_y->y1;		//dy = y2 - y1
		// while(ray_y->y2 <= WINHEIGHT && ray_y->y2 >= 0 && ray_y->x2 <= WINWIDTH && ray_y->x2 >= 0)
		// {
		// 	if(is_wall(data, ray_y->y2, ray_y->x2))
		// 		return ;
		// 	else
		// 	{
		// 		ray_y->x2 = find_next_wall(ray_y->x2 + 1, 1);
		// 		ray_y->y2 = find_y(ray_y->x1, ray_y->y1, ray_y->x2, data->angle);
		// 		ray_y->dx = ray_y->x2 - ray_y->x1;		// dx = x2 - x1
		// 		ray_y->dy = ray_y->y2 - ray_y->y1;
		// 	}			//dy = y2 - y1
		// }
	}
	if(data->angle >  90 && data->angle <= 270)
	{
		ray_y->x2 = find_next_wall(ray_y->x1, 1);
		ray_y->dx =  ray_y->x2 - ray_y->x1;
		ray_y->y2 = find_y(ray_y->x1, ray_y->y1, ray_y->x2, data->angle);	// dx = x2 - x1
		ray_y->dy = ray_y->y2 - ray_y->y1;		//dy = y2 - y1
		// while(ray_y->y2 <= WINHEIGHT && ray_y->y2 >= 0 && ray_y->x2 <= WINWIDTH && ray_y->x2 >= 0)
		// {
		// 	if(is_wall(data, ray_y->y2, ray_y->x2))
		// 		return ;
		// 	else
		// 	{
		// 		ray_y->x2 = find_next_wall(ray_y->x2 - 1, - 1);
		// 		ray_y->y2 = find_y(ray_y->x1, ray_y->y1, ray_y->x2, data->angle);
		// 		ray_y->dx = ray_y->x2 - ray_y->x1;		// dx = x2 - x1
		// 		ray_y->dy = ray_y->y2 - ray_y->y1;
		// 	}			//dy = y2 - y1
		// }
	}
	if (fabs(ray_y->dx) > fabs(ray_y->dy))
		ray_y->steps = fabs(ray_y->dx);
	else
		ray_y->steps = fabs(ray_y->dy);
}
void	dda_algorithm(t_data *data, double x1, double y1, mlx_image_t *drawline)
{
	int		i;
	int		steps;
	double	xinc;
	double	yinc;
	double	x;
	double	y;
	t_ray	ray_x;
	t_ray	ray_y;

	ray_x.x1 = x1;
	ray_x.y1 = y1;
	ray_y.x1 = x1;
	ray_y.y1 = y1;
	x = 0;
	y = 0;
	i = 1;
	calc_ray_x(data, &ray_x);
	calc_ray_y(data, &ray_y);
	printf("ANGLE %f\n", data->angle);
	if (ray_x.steps < ray_y.steps)
	{
		steps = ray_x.steps;
		xinc = ray_x.dx / steps;
		yinc = ray_x.dy / steps;
		x = ray_x.x1;
		y = ray_x.y1;
	}
	else
	{
		steps = ray_y.steps;
		xinc = ray_y.dx / steps;
		yinc = ray_y.dy / steps;
		x = ray_y.x1;
		y = ray_y.y1;
	}
	while (i++ <= steps)
	{
		mlx_put_pixel(drawline, x, y, 0xFF0000FF);
		x = x + xinc;
		y = y + yinc;
	}
}