/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zparsing_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:41:56 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/12 16:13:17 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	parse_map(t_data *data, int y)
{
	int	x;

	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1' || data->map[y][x] == '0'
				|| data->map[y][x] == ' ' || data->map[y][x] == '2')
			{
				if (data->map[y][x] == ' ')
					data->map[y][x] = '0';
				x++;
			}
			else if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'W' || data->map[y][x] == 'E')
				x = player_position(data, y, x);
			else
				cub_exit(data, ERRCHAR);
		}
		y++;
	}
	if (data->player.map_x == -1 || data->player.map_x == -1)
		cub_exit(data, ERRNOPLAYER);
}

int	check_floor(t_data *data)
{
	if (ft_strncmp(&data->map[data->y][data->x], "F ", 2) == 0)
	{
		color_decoder(data, &data->map[data->y][data->x + 2],
			&data->param.floor);
		data->param.flgfloor = 1;
		return (1);
	}
	else if (ft_strncmp(&data->map[data->y][data->x], "C ", 2) == 0)
	{
		color_decoder(data, &data->map[data->y][data->x + 2],
			&data->param.ceil);
		data->param.flgceil = 1;
		return (1);
	}
	return (0);
}

int	check_door(t_data *data)
{
	if (ft_strncmp(&data->map[data->y][data->x], "DO ", 3) == 0)
	{
		data->param.door = check_path(data, &data->map[data->y][data->x + 3]);
		return (1);
	}
	return (0);
}

int	check_directions(t_data *data)
{
	if (ft_strncmp(&data->map[data->y][data->x], "NO ", 3) == 0)
	{
		data->param.north = check_path(data, &data->map[data->y][data->x + 3]);
		return (1);
	}
	else if (ft_strncmp(&data->map[data->y][data->x], "SO ", 3) == 0)
	{
		data->param.south = check_path(data, &data->map[data->y][data->x + 3]);
		return (1);
	}
	else if (ft_strncmp(&data->map[data->y][data->x], "WE ", 3) == 0)
	{
		data->param.west = check_path(data, &data->map[data->y][data->x + 3]);
		return (1);
	}
	else if (ft_strncmp(&data->map[data->y][data->x], "EA ", 3) == 0)
	{
		data->param.east = check_path(data, &data->map[data->y][data->x + 3]);
		return (1);
	}
	return (0);
}

void	parsing(t_data *data)
{
	data->y = -1;
	while (data->map[++data->y])
	{
		data->x = -1;
		while (data->map[data->y][++data->x])
		{
			while (data->map[data->y][data->x] == ' '
				&& data->map[data->y][data->x] == '\t'
				&& data->map[data->y][data->x])
				data->x++;
			if (data->map[data->y][data->x] == '\0')
				break ;
			if (check_directions(data) == 1)
				break ;
			else if (check_door(data) == 1)
				break ;
			else if (check_floor(data) == 1)
				break ;
			else if (check_start_map(data) == 1)
				break ;
		}
		if (data->map[data->y][data->x] == '1')
			break ;
	}
	parse_map(data, data->player.start_map);
}
