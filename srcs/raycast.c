/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:02:49 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/02 16:57:04 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_game(t_data *data)
{
	data->ray.pos.x = (double)data->player.pos_y / MINITILES + (0.5);
	data->ray.pos.y = (double)data->player.pos_x / MINITILES + (0.5);
	//TODO: attributes the correct orientation per the data->map (N, W, S, E)
	// iniiral direction vector (where the player looks)
	// cam plane

	data->ray.cam_x = 0;
	data->ray.side_dist.x = 0;
	data->ray.side_dist.y = 0;
	data->ray.delta_dist.x = 0;
	data->ray.delta_dist.y = 0;

	data->ray.step.x = 1;
	data->ray.step.y = 1;
	data->ray.cam_angle = 0.5;
}

void	set_data(t_data *data)
{
	//set ray dir
	data->ray.ray_dir.x = data->ray.dir.x + \
		data->ray.plane.x * data->ray.cam_x;
	data->ray.ray_dir.y = data->ray.dir.y + \
		data->ray.plane.y * data->ray.cam_x;
	
	//set map pos
	data->ray.coord.x = data->ray.pos.x;
	data->ray.coord.y = data->ray.pos.y;

	//set delta dist
	data->ray.delta_dist.x = fabs(1 / data->ray.ray_dir.x);
	data->ray.delta_dist.y = fabs(1 / data->ray.ray_dir.y);
}

void	set_side_dist(t_data *data)
{
	if(data->ray.ray_dir.x < 0)
	{
		data->ray.step.x = -0.01;
		data->ray.side_dist.x = (data->ray.pos.x - \
			data->ray.coord.x) * data->ray.delta_dist.x;
	}
	else
	{
		data->ray.step.x = 0.01;
		data->ray.side_dist.x = (data->ray.coord.x + 1.0 - \
			data->ray.pos.x) * data->ray.delta_dist.x;
	}
	if(data->ray.ray_dir.y < 0)
	{
		data->ray.step.y = -0.01;
		data->ray.side_dist.y = (data->ray.pos.y - \
			data->ray.coord.y) * data->ray.delta_dist.y;
	}
	else
	{
		data->ray.step.y = 0.01;
		data->ray.side_dist.y = (data->ray.coord.y + 1.0 - \
			data->ray.pos.y) * data->ray.delta_dist.y;
	}
}

void	dda(t_data *data)
{
	while(1)
	{
		
		if(data->ray.side_dist.x < data->ray.side_dist.y)
		{
			data->ray.side_dist.x += data->ray.delta_dist.x;
			data->ray.coord.x += data->ray.step.x;
			//keep in case of norm too tough on set_side_dist
			// if(data->ray.ray_dir.x < 0)
			// 	data->ray.coord.x -= 0.01;
			// else
			// 	data->ray.coord.x += 0.01;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist.y += data->ray.delta_dist.y;
			data->ray.coord.y += data->ray.step.y;
			//keep in case of norm too tough on set_side_dist
			// if(data->ray.ray_dir.y < 0)
			// 	data->ray.coord.y -= 0.01; 
			// else
			// 	data->ray.coord.y += 0.01;

			data->ray.side = 1;
		}
		if(data->map[(int)data->ray.coord.x][(int)data->ray.coord.y] == '1')
			break;

	}
	if(data->ray.side == 0)
			data->ray.perp_wall_dist = (data->ray.side_dist.x - data->ray.delta_dist.x);
	else
			data->ray.perp_wall_dist = (data->ray.side_dist.y - data->ray.delta_dist.y);
}


void	set_draw_range(t_data *data)
{
	data->ray.line_height = (int)((WINHEIGHT * 110) / data->ray.perp_wall_dist); //add to add multiply HEIGHT by 125 to smooth mvt (110 more squared)
	data->ray.draw_start = -data->ray.line_height * 0.5 + WINHEIGHT * data->ray.cam_angle;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = data->ray.line_height * 0.5 + WINHEIGHT * data->ray.cam_angle;
	if (data->ray.draw_end >= WINHEIGHT)
		data->ray.draw_end = WINHEIGHT - 1;
}

void	draw_vertline(t_data *data, int x)
{
	int	y;
	
	y = 0;
	// printf("%d", data->ray.draw_end);
	while((int)y < data->ray.draw_start)
		mlx_put_pixel(data->image.window, x, y++, data->param.ceil); //ceiling color (Black)ft_color(48,127,207,255
	while((int)y < data->ray.draw_end)
		mlx_put_pixel(data->image.window, x, y++, data->param.wall); // red
	while((int)y < WINHEIGHT)
		mlx_put_pixel(data->image.window, x, y++, data->param.floor); //floor color (white)ft_color(30,30,30,255)
}

void	wall_color(t_data *data)
{
	if(data->ray.side == 1 && data->ray.ray_dir.y > 0)
		data->param.wall = ft_color(127, 255, 255, 255);
	if(data->ray.side == 1 && data->ray.ray_dir.y < 0)
		data->param.wall = ft_color(255, 127, 255, 255);
	if(data->ray.side == 0 && data->ray.ray_dir.x > 0)
		data->param.wall = ft_color(255, 255, 127, 255);
	if(data->ray.side == 0 && data->ray.ray_dir.x < 0)
		data->param.wall = ft_color(127, 127, 255, 255);
}



void	loop(void *param)
{
	t_data		*data;
	int	x;

	data = param;
	x = -1;
	
	
	while(++x < WINWIDTH)
	{
		data->ray.cam_x = 2 * x / (double)WINWIDTH - 1;
		set_data(data);
		set_side_dist(data);
		dda(data);
		set_draw_range(data);
		wall_color(data);
		draw_vertline(data, x);
		key_binding(data);
		mouse_tracking(data);
	}
	usleep(3000);
}

