/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:52:39 by emlamoth          #+#    #+#             */
/*   Updated: 2023/10/05 10:06:54 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	if(mlx_is_key_down(data->mlx, MLX_KEY_UP))
		if(data->ray.cam_angle < 1)
			data->ray.cam_angle += 0.00002;
	if(mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		if(data->ray.cam_angle > 0)
			data->ray.cam_angle -= 0.00002;
}

void	mouse_tracking(t_data *data)
{
	int32_t	y;
	int32_t	x;

	y = 0;
	x = 0;
	mlx_get_mouse_pos(data->mlx, &x, &y);
<<<<<<< HEAD
	if(data->view == 2 && y < WINHEIGHT / 2)
	{
		if(data->ray.cam_angle < 1)
			data->ray.cam_angle += 0.015;
	}
	if(data->view == 2 && y > WINHEIGHT / 2)
	{
		if(data->ray.cam_angle > 0)
			data->ray.cam_angle -= 0.015;
	}
	if(data->view > 0 && x < WINWIDTH / 2)
=======
	if(x < WINWIDTH / 2)
>>>>>>> finaly working
	{
		rotate_vector(&data->ray.dir.x, &data->ray.dir.y, ROTATE_SPEED * MOUSE_SPEED);
		rotate_vector(&data->ray.plane.x, &data->ray.plane.y, ROTATE_SPEED * MOUSE_SPEED);
	}
	if(x > WINWIDTH / 2)
	{
		rotate_vector(&data->ray.dir.x, &data->ray.dir.y, -ROTATE_SPEED * MOUSE_SPEED);
		rotate_vector(&data->ray.plane.x, &data->ray.plane.y, -ROTATE_SPEED * MOUSE_SPEED);
	}
	if(y != WINHEIGHT / 2 || x != WINWIDTH / 2)
		mlx_set_mouse_pos(data->mlx, WINWIDTH / 2, WINHEIGHT / 2);
	
}

void	ft_key_detect(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_V)
	{
		if(data->view <= 1)
			data->view++;
		else
		{
			data->view = 0;
			data->ray.cam_angle = 0.5;
		}	
	}
	key_binding(data);
	mouse_tracking(data);
}

//TODO corner spawn