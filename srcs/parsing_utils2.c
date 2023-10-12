/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:06:21 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/12 13:41:16 by fbouchar         ###   ########.fr       */
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

void	color_decoder(t_data *data, char *str, uint32_t *surface)
{
	int			i;
	uint32_t	temp;
	char		*temp_str;

	temp_str = NULL;
	temp_str = ft_strtrim(str, " ");
	if (!temp_str)
		cub_exit(data, ERRMALLOC);
	i = 0;
	*surface = 0;
	while (temp_str[i] && i < 12)
	{
		temp = (uint32_t)ft_atoi(temp_str + i);
		if (temp < 0 || temp > 255)
			cub_exit(data, ERRCOLOR);
		*surface = *surface << 8;
		*surface |= temp;
		while (temp_str[i] && temp_str[i] != ',')
			i++;
		if (temp_str[i])
			i++;
	}
	*surface = *surface << 8;
	*surface |= 255;
	free(temp_str);
}
