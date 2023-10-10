/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:06:21 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/10 11:07:49 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_start_map(t_data *data)
{
	if (data->map[data->y][data->x] == '1' && ((!data->param.north)
		|| (!data->param.south) || (!data->param.west)
		|| (!data->param.east) || (data->param.flgceil == 0)
		|| (data->param.flgfloor == 0)))
	{
		cub_exit(data, ERRPARSE);
		return (1);
	}
	else if (data->map[data->y][data->x] == '1')
	{
		data->player.start_map = data->y;
		return (1);
	}
	return (0);
}

int	player_position(t_data *data, int y, int x)
{
	if (data->player.map_y == -1)
	{
		data->player.map_x = x;
		data->player.map_y = y;
		data->player.pos_x = data->player.map_x * MINITILES;
		data->player.pos_y = data->player.map_y * MINITILES
			- (data->player.start_map * MINITILES);
		set_dir(data, data->map[y][x]);
		data->map[y][x] = '0';
		x++;
	}
	else
		cub_exit(data, ERRPLAYER);
	return (x);
}
