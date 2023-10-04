/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:02:49 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/04 14:52:38 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_game(t_data *data)
{
	data->ray.pos.x = (double)data->player.pos_y / MINITILES + (0.5);
	data->ray.pos.y = (double)data->player.pos_x / MINITILES + (0.5);
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
	data->ray.ray_dir.x = data->ray.dir.x + data->ray.plane.x * data->ray.cam_x;
	data->ray.ray_dir.y = data->ray.dir.y + data->ray.plane.y * data->ray.cam_x;
	data->ray.coord.x = data->ray.pos.x;
	data->ray.coord.y = data->ray.pos.y;
	data->ray.delta_dist.x = fabs(1 / data->ray.ray_dir.x);
	data->ray.delta_dist.y = fabs(1 / data->ray.ray_dir.y);
}

void	set_side_dist(t_data *data)
{
	if(data->ray.ray_dir.x < 0)
	{
		data->ray.step.x = -1;
		data->ray.side_dist.x = (data->ray.pos.x - data->ray.coord.x) * data->ray.delta_dist.x;
	}
	else
	{
		data->ray.step.x = 1;
		data->ray.side_dist.x = (data->ray.coord.x + 1.0 - data->ray.pos.x) * data->ray.delta_dist.x;
	}
	if(data->ray.ray_dir.y < 0)
	{
		data->ray.step.y = -1;
		data->ray.side_dist.y = (data->ray.pos.y - data->ray.coord.y) * data->ray.delta_dist.y;
	}
	else
	{
		data->ray.step.y = 1;
		data->ray.side_dist.y = (data->ray.coord.y + 1.0 - data->ray.pos.y) * data->ray.delta_dist.y;
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
		if(data->map[(int)data->ray.coord.x][(int)data->ray.coord.y] == '1')
			break;
	}
	if(data->ray.side < 2)
			data->ray.perp_wall_dist = (data->ray.side_dist.x - data->ray.delta_dist.x);
	else
			data->ray.perp_wall_dist = (data->ray.side_dist.y - data->ray.delta_dist.y);
}


void	set_draw_range(t_data *data)
{
	data->ray.line_height = (int)((WINHEIGHT) / data->ray.perp_wall_dist);
	data->ray.draw_start = -data->ray.line_height * 0.5 + WINHEIGHT * data->ray.cam_angle;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = data->ray.line_height * 0.5 + WINHEIGHT * data->ray.cam_angle;
	if (data->ray.draw_end >= WINHEIGHT)
		data->ray.draw_end = WINHEIGHT;
}


void	wall_color(t_data *data)
{
	if(data->ray.side == 0)
		data->param.wall = ft_color(127, 255, 255, 255);
	if(data->ray.side == 1)
		data->param.wall = ft_color(255, 127, 255, 255);
	if(data->ray.side == 2)
		data->param.wall = ft_color(255, 255, 127, 255);
	if(data->ray.side == 3)
		data->param.wall = ft_color(127, 127, 255, 255);
}

void	find_hit(t_data *data, mlx_texture_t *texture)
{
	double	hit;

	hit = 0;
	if (data->ray.side == 0 || data->ray.side == 1)
		hit = data->ray.pos.y + data->ray.perp_wall_dist * data->ray.ray_dir.y;
	else
		hit = data->ray.pos.x + data->ray.perp_wall_dist * data->ray.ray_dir.x;
	hit -= (int) hit;
	data->ray.tex_x = (int)(hit * (double) texture->width);

	if ((data->ray.side == 0 || data->ray.side == 1) && data->ray.ray_dir.x > 0)
		data->ray.tex_x = texture->width - data->ray.tex_x - 1;
	if ((data->ray.side == 2 || data->ray.side == 3) && data->ray.ray_dir.y < 0)
		data->ray.tex_x = texture->width - data->ray.tex_x - 1;
}

void	drawline(t_data *data, mlx_texture_t *texture, uint32_t **arr, int x)
{
	double	dist;
	double	pos;
	int		tex_y;
	int		j;

	dist = 1.0 * texture->height / data->ray.line_height;
	pos = ((double) data->ray.draw_start - (double) WINHEIGHT / 2
			+ (double) data->ray.line_height / 2) * dist;
	if (pos < 0)
		pos = 0;
	j = data->ray.draw_start - 1;
	while (++j < data->ray.draw_end)
	{
		tex_y = (int) pos;
		if (pos > texture->height - 1)
			pos = texture->height - 1;
		pos += dist;
		mlx_put_pixel(data->image.window, x, j, arr[tex_y][data->ray.tex_x]);
	}
}

void	choose_texture(t_data *data, int x)
{
	if (data->ray.side == 0)
	{
		find_hit(data, data->texture.east_tex);
		drawline(data, data->texture.east_tex, data->texture.east, x);
	}
	else if (data->ray.side == 1)
	{
		find_hit(data, data->texture.west_tex);
		drawline(data, data->texture.west_tex, data->texture.west, x);
	}
	else if (data->ray.side == 2)
	{
		find_hit(data, data->texture.south_tex);
		drawline(data, data->texture.south_tex, data->texture.south, x);
	}
	else
	{
		find_hit(data, data->texture.north_tex);
		drawline(data, data->texture.north_tex, data->texture.north, x);
	}
}

void	draw_vertline(t_data *data, int x)
{
	int	y;
	
	y = 0;
	while((int)y < WINHEIGHT / 2)
		mlx_put_pixel(data->image.window, x, y++, data->param.ceil); //ceiling color
	while((int)y < WINHEIGHT)
		mlx_put_pixel(data->image.window, x, y++, data->param.floor); //floor color
}

void	loop(void *param)
{
	t_data		*data;
	// int	x;

	data = param;
	// x = -1;
	raycast2(data);
	
	// while(++x < WINWIDTH)
	// {
	// 	data->ray.cam_x = 2 * x / (double)WINWIDTH - 1;
	// 	set_data(data);
	// 	draw_vertline(data, x);
	// 	// set_side_dist(data);
	// 	// dda(data);
	// 	// set_draw_range(data);
	// 	// choose_texture(data, x);
	// 	// key_binding(data);
	// 	// mouse_tracking(data);
	// }
	// usleep(3000);
}
