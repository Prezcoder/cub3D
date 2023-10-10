/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:20:23 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/10 11:12:31 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_data(t_data *data, int x)
{
	data->ray.cam_x = 2 * x / (double)WINWIDTH - 1;
	data->ray.ray_dir.x = data->ray.dir.x
		+ data->ray.plane.x * data->ray.cam_x;
	data->ray.ray_dir.y = data->ray.dir.y
		+ data->ray.plane.y * data->ray.cam_x;
	data->ray.coord.x = (int)data->ray.pos.x;
	data->ray.coord.y = (int)data->ray.pos.y;
	data->ray.delta_dist.x = fabs(1 / data->ray.ray_dir.x);
	data->ray.delta_dist.y = fabs(1 / data->ray.ray_dir.y);
}

void	set_side_dist(t_data *data)
{
	if (data->ray.ray_dir.x < 0)
	{
		data->ray.step.x = -1;
		data->ray.side_dist.x = (data->ray.pos.x - data->ray.coord.x)
			* data->ray.delta_dist.x;
	}
	else
	{
		data->ray.step.x = 1;
		data->ray.side_dist.x = (data->ray.coord.x + 1.0 - data->ray.pos.x)
			* data->ray.delta_dist.x;
	}
	if (data->ray.ray_dir.y < 0)
	{
		data->ray.step.y = -1;
		data->ray.side_dist.y = (data->ray.pos.y - data->ray.coord.y)
			* data->ray.delta_dist.y;
	}
	else
	{
		data->ray.step.y = 1;
		data->ray.side_dist.y = (data->ray.coord.y + 1.0 - data->ray.pos.y)
			* data->ray.delta_dist.y;
	}
}

void	dda_calc(t_data *data)
{
	if (data->ray.side_dist.x < data->ray.side_dist.y)
	{
		data->ray.side_dist.x += data->ray.delta_dist.x;
		data->ray.coord.x += data->ray.step.x;
		if (data->ray.ray_dir.x > 0)
			data->ray.side = 0;
		else
			data->ray.side = 1;
	}
	else
	{
		data->ray.side_dist.y += data->ray.delta_dist.y;
		data->ray.coord.y += data->ray.step.y;
		if (data->ray.ray_dir.y > 0)
			data->ray.side = 2;
		else
			data->ray.side = 3;
	}
}

void	dda(t_data *data)
{
	while (1)
	{
		dda_calc(data);
		if (data->map[(int)data->ray.coord.x][(int)data->ray.coord.y] == '1')
			break ;
		if (data->map[(int)data->ray.coord.x][(int)data->ray.coord.y] == '2')
		{
			data->texture.door_flag = 1;
			break ;
		}
	}
	if (data->ray.side < 2)
		data->ray.perp_wall_dist = (data->ray.side_dist.x
				- data->ray.delta_dist.x);
	else
		data->ray.perp_wall_dist = (data->ray.side_dist.y
				- data->ray.delta_dist.y);
}

void	set_draw_range(t_data *data)
{
	data->ray.line_height = (int)WINHEIGHT / data->ray.perp_wall_dist;
	data->ray.draw_start = -data->ray.line_height * 0.5 + WINHEIGHT
		* data->ray.cam_angle;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = data->ray.line_height * 0.5 + WINHEIGHT
		* data->ray.cam_angle;
	if (data->ray.draw_end >= WINHEIGHT)
		data->ray.draw_end = WINHEIGHT;
}
