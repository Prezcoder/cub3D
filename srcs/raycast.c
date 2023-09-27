/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:02:49 by fbouchar          #+#    #+#             */
/*   Updated: 2023/09/27 15:34:50 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_game(t_data *data)
{
	data->ray.pos.x = (double)data->player.pos_y / MINITILES;
	data->ray.pos.y = (double)data->player.pos_x / MINITILES;

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
	data->ray.line_height = (int)((WINHEIGHT * 125) / data->ray.perp_wall_dist); //add to add multiply HEIGHT by 125 to smooth mvt
	data->ray.draw_start = -data->ray.line_height * 0.5 + WINHEIGHT * 0.5;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = data->ray.line_height * 0.5 + WINHEIGHT * 0.5;
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

void	rotate_vector(double *x, double *y, double angle) 
{
	double old_x ;

	old_x = *x;
	*x = old_x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
}

void	move_player(t_data *data, double move_speed) 
{
	double checkRadius = 0.3;
    // Move along X direction
	if (move_speed < 0)
		checkRadius = -0.3;
    if(data->map[(int)(data->ray.pos.x + data->ray.dir.x * (move_speed + checkRadius))][(int)data->ray.pos.y] == '0')
        data->ray.pos.x += data->ray.dir.x * move_speed;
    
    // Move along Y direction
    if(data->map[(int)data->ray.pos.x][(int)(data->ray.pos.y + data->ray.dir.y * (move_speed + checkRadius))] == '0')
        data->ray.pos.y += data->ray.dir.y * move_speed;
}

void strafe_player(t_data *data, double strafe_speed) 
{
	double checkRadius = 0.3;
	if (strafe_speed < 0)
		checkRadius = -0.3;
    if(data->map[(int)(data->ray.pos.x + data->ray.dir.y * (strafe_speed + checkRadius))][(int)data->ray.pos.y] == '0')
        data->ray.pos.x += data->ray.dir.y * strafe_speed;
    
    if(data->map[(int)data->ray.pos.x][(int)(data->ray.pos.y - data->ray.dir.x * (strafe_speed + checkRadius))] == '0')
        data->ray.pos.y -= data->ray.dir.x * strafe_speed;
}

void	key_binding(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
			mlx_close_window(data->mlx);

	if (mlx_is_key_down(data->mlx, MLX_KEY_W)) 
		move_player(data, MOVE_SPEED); // Move forward
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, -MOVE_SPEED); // Move backward

	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		strafe_player(data, -MOVE_SPEED); // Strafe left
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		strafe_player(data, MOVE_SPEED); // Strafe right

	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)) 
	{
		rotate_vector(&data->ray.dir.x, &data->ray.dir.y, -ROTATE_SPEED);
		rotate_vector(&data->ray.plane.x, &data->ray.plane.y, -ROTATE_SPEED);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)) 
	{
		rotate_vector(&data->ray.dir.x, &data->ray.dir.y, ROTATE_SPEED);
		rotate_vector(&data->ray.plane.x, &data->ray.plane.y, ROTATE_SPEED);
	}
	// printf("X %f\n", data->ray.dir.x);
	// printf("Y %f\n", data->ray.dir.y);
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
	}
}

