/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zdoor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:20:18 by emlamoth          #+#    #+#             */
/*   Updated: 2023/10/12 12:31:50 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

void	door(t_data *data)
{
	if (open_door(data))
		return ;
	close_door(data);
}
