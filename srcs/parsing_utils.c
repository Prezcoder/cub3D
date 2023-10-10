/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:04:27 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/10 11:05:02 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	cub_exit(t_data *data, char *msg)
{
	errhandler(msg);
	ft_freeall(data->map);
	//TODO free param.north, south, door, etc;
	exit(-1);
}

void	color_decoder(t_data *data, char *str, uint32_t *surface)
{
	int			i;
	uint32_t	temp;
	char		*temp_str;

	temp_str = NULL;
	temp_str = ft_strtrim(str, " ");
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
