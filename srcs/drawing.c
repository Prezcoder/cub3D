/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:30:07 by fbouchar          #+#    #+#             */
/*   Updated: 2023/09/19 09:42:57 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	dda_algorithm(int x1, int x2, int y1, int y2, mlx_image_t *drawline)
{
	int	i;
	int	dx;
	int	dy;
	int	steps;
	double	xinc;
	double	yinc;

	i = 1;
	steps = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	xinc = dx / steps;
	yinc = dy / steps;
	while (i++ <= steps)
	{
		mlx_put_pixel(drawline, x1, y1, 111);
		x1 = x1 + xinc;
		y1 = y1 + yinc;
	}
}