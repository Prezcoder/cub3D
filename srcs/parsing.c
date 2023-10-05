/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:41:56 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/05 14:35:47 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	cub_exit(t_data *data, char *msg)
{
	errhandler(msg);
	ft_freeall(data->map);
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
	char *wall;
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

int	player_position(t_data *data, int y, int x)
{
	if(data->player.map_y == -1)
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

void	parse_map(t_data *data, int y)
{	
	int x;

	while(data->map[y])
	{
		x = 0;
		while(data->map[y][x])
		{
			if(data->map[y][x] == '1' || data->map[y][x] == '0'
				|| data->map[y][x] == ' ')
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
	if(data->player.map_x == -1 || data->player.map_x == -1)
		cub_exit(data, ERRNOPLAYER);
}

// void	check_directions(t_data *data, int y, int x)
// {
// 	if (ft_strncmp(&data->map[y][x], "NO ", 3) == 0)
// 		data->param.north = check_path(data, &data->map[y][x + 3]);
// 	else if (ft_strncmp(&data->map[y][x], "SO ", 3) == 0)
// 		data->param.south = check_path(data, &data->map[y][x + 3]);
// 	else if (ft_strncmp(&data->map[y][x], "WE ", 3) == 0)
// 		data->param.west = check_path(data, &data->map[y][x + 3]);
// 	else if (ft_strncmp(&data->map[y][x], "EA ", 3) == 0)
// 		data->param.east = check_path(data, &data->map[y][x + 3]);
// 	else if (ft_strncmp(&data->map[y][x], "F ", 2) == 0)
// 	{
// 		color_decoder(data, &data->map[y][x + 2], &data->param.floor);
// 		data->param.flgfloor = 1;
// 		x = -1;
// 		y++;
// 	}
// 	else if (ft_strncmp(&data->map[y][x], "C ", 2) == 0)
// 	{
// 		color_decoder(data, &data->map[y][x + 2], &data->param.ceil);
// 		data->param.flgceil = 1;
// 		x = -1;
// 		y++;
// 	}
// 	else if (data->map[y][x] == '1' && ((!data->param.north)
// 		|| (!data->param.south) || (!data->param.west)
// 		|| (!data->param.east) || (data->param.flgceil == 0)
// 		|| (data->param.flgfloor == 0)))
// 		cub_exit(data, ERRPARSE);
// 	else if (data->map[y][x] == '1')
// 	{
// 		data->player.start_map = y;
// 		break;
// 	}
// }

void	parsing(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			while (data->map[y][x] == ' ' && data->map[y][x] == '\t' && data->map[y][x])
				x++;
			if (data->map[y][x] == '\0')
				break;
			if (ft_strncmp(&data->map[y][x], "NO ", 3) == 0)
				data->param.north = check_path(data, &data->map[y][x + 3]);
			else if (ft_strncmp(&data->map[y][x], "SO ", 3) == 0)
				data->param.south = check_path(data, &data->map[y][x + 3]);
			else if (ft_strncmp(&data->map[y][x], "WE ", 3) == 0)
				data->param.west = check_path(data, &data->map[y][x + 3]);
			else if (ft_strncmp(&data->map[y][x], "EA ", 3) == 0)
				data->param.east = check_path(data, &data->map[y][x + 3]);
			else if (ft_strncmp(&data->map[y][x], "F ", 2) == 0)
			{
				color_decoder(data, &data->map[y][x + 2], &data->param.floor);
				data->param.flgfloor = 1;
				x = -1;
				y++;
			}
			else if (ft_strncmp(&data->map[y][x], "C ", 2) == 0)
			{
				color_decoder(data, &data->map[y][x + 2], &data->param.ceil);
				data->param.flgceil = 1;
				x = -1;
				y++;
			}
			else if (data->map[y][x] == '1' && ((!data->param.north)
				|| (!data->param.south) || (!data->param.west)
				|| (!data->param.east) || (data->param.flgceil == 0)
				|| (data->param.flgfloor == 0)))
				cub_exit(data, ERRPARSE);
			else if (data->map[y][x] == '1')
			{
				data->player.start_map = y;
				break;
			}
		}
		if (data->map[y][x] == '1')
			break;
	}
	parse_map(data, data->player.start_map);
}

//TODO les path de map avec des chiffres ne fonctionne pas