/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:04:27 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/12 09:12:00 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	free_param(t_data *data)
{
	if (data->param.north)
		ft_freenull(&data->param.north);
	if (data->param.south)
		ft_freenull(&data->param.south);
	if (data->param.west)
		ft_freenull(&data->param.west);
	if (data->param.east)
		ft_freenull(&data->param.east);
	if (data->param.door)
		ft_freenull(&data->param.door);
}

void	cub_exit(t_data *data, char *msg)
{
	errhandler(msg);
	ft_freeall(data->map);
	free_param(data);
	exit(-1);
}

char	*check_path(t_data *data, char *str)
{
	char	*wall;

	wall = ft_strtrim(str, " ");
	if (wall == NULL)
		cub_exit(data, ERRIMG);
	if (open(wall, O_RDONLY) == -1)
		cub_exit(data, ERRIMG);
	return (wall);
}

void	set_dir2(t_data *data, char c)
{
	if (c == 'S')
	{
		data->ray.dir.x = 1;
		data->ray.dir.y = 0;
		data->ray.plane.x = 0;
		data->ray.plane.y = -0.66;
		data->angle = 90;
	}
	if (c == 'N')
	{
		data->ray.dir.x = -1;
		data->ray.dir.y = 0;
		data->ray.plane.x = 0;
		data->ray.plane.y = 0.66;
		data->angle = 270;
	}
}

void	set_dir(t_data *data, char c)
{
	if (c == 'W')
	{
		data->ray.dir.x = 0;
		data->ray.dir.y = -1;
		data->ray.plane.x = -0.66;
		data->ray.plane.y = 0;
		data->angle = 180;
	}
	if (c == 'E')
	{
		data->ray.dir.x = 0;
		data->ray.dir.y = 1;
		data->ray.plane.x = 0.66;
		data->ray.plane.y = 0;
		data->angle = 0;
	}
	else
		(set_dir2(data, c));
}
