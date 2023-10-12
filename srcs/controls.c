/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:52:39 by emlamoth          #+#    #+#             */
/*   Updated: 2023/10/12 11:21:47 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	key_binding(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player(data, MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, -MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		strafe_player(data, -MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		strafe_player(data, MOVE_SPEED);
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
}

void	mouse_tracking(t_data *data) // enlever pour downgrade
{
	int32_t	y;
	int32_t	x;

	y = 0;
	x = 0;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (data->view > 0 && x < WINWIDTH / 2)
	{
		rotate_vector(&data->ray.dir.x, &data->ray.dir.y,
			ROTATE_SPEED * MOUSE_SPEED);
		rotate_vector(&data->ray.plane.x, &data->ray.plane.y,
			ROTATE_SPEED * MOUSE_SPEED);
	}
	if (data->view > 0 && x > WINWIDTH / 2)
	{
		rotate_vector(&data->ray.dir.x, &data->ray.dir.y,
			-ROTATE_SPEED * MOUSE_SPEED);
		rotate_vector(&data->ray.plane.x, &data->ray.plane.y,
			-ROTATE_SPEED * MOUSE_SPEED);
	}
	if (y != WINHEIGHT / 2 || x != WINWIDTH / 2)
		mlx_set_mouse_pos(data->mlx, WINWIDTH / 2, WINHEIGHT / 2);
}

int	open_door(t_data *data)
{
	double	checkradius;

	checkradius = 1.2;
	if (data->map[(int)(data->ray.pos.x + data->ray.dir.x * checkradius)]
		[(int)data->ray.pos.y] == '2')
	{
		data->map[(int)(data->ray.pos.x + data->ray.dir.x * checkradius)]
		[(int)data->ray.pos.y] = '3';
		system("afplay ./music/door_open.wav&");
		return (1);
	}
	else if (data->map[(int)data->ray.pos.x][(int)(data->ray.pos.y
		+ data->ray.dir.y * checkradius)] == '2')
	{
		data->map[(int)data->ray.pos.x][(int)(data->ray.pos.y
				+ data->ray.dir.y * checkradius)] = '3';
		system("afplay ./music/door_open.wav&");
		return (1);
	}
	return (0);
}

void	close_door(t_data *data)
{
	double	checkradius;

	checkradius = 1.2;
	if (data->map[(int)(data->ray.pos.x + data->ray.dir.x * checkradius)]
		[(int)data->ray.pos.y] == '3')
	{
		data->map[(int)(data->ray.pos.x + data->ray.dir.x * checkradius)]
		[(int)data->ray.pos.y] = '2';
		system("afplay ./music/door_close.wav&");
	}
	else if (data->map[(int)data->ray.pos.x][(int)(data->ray.pos.y
		+ data->ray.dir.y * checkradius)] == '3')
	{
		data->map[(int)data->ray.pos.x][(int)(data->ray.pos.y
				+ data->ray.dir.y * checkradius)] = '2';
		system("afplay ./music/door_close.wav&");
	}
}

void	door(t_data *data) //TODO enlever pour downgrade
{
	if(open_door(data))
		return;
	close_door(data);
}

void	ft_key_detect(mlx_key_data_t keydata, void *param) //TODO enlever pour downgrade
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_V)
	{		
		if (data->view == 0)
			data->view = 1;
		else
			data->view = 0;
	}
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_F)
		door(data);
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_LEFT_SUPER)
		data->view = 0;
}
