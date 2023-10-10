/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:54:57 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/10 10:52:47 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_data	*init_data(t_data *data, char **argv)
{
	if (!argv)
		return (data);
	ft_bzero(data, sizeof(t_data));
	data->player.map_x = -1;
	data->player.map_y = -1;
	return (data);
}

int	init_aray(t_data *data, char *path)
{
	int		fd;
	int		i;
	char	*temp;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	temp = get_next_line(fd);
	while (temp)
	{
		ft_freenull(&temp);
		temp = get_next_line(fd);
		i++;
	}
	data->param.nbline = i;
	close(fd);
	data->map = ft_calloc(i + 1, sizeof(char *));
	return (0);
}

int	init_map(t_data *data, char *path)
{
	int		fd;
	int		i;
	int		len;
	
	if(init_aray(data, path) == -1)
		return (errhandler(ERRMAP));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (errhandler(ERRMAP));
	i = 0;
	data->map[i] = get_next_line(fd);	
	len = ft_strlen(data->map[i]);
	if (data->map[i][len - 1] == '\n')
		data->map[i][len - 1] = 0;
	while (data->map[i++])
	{
		data->map[i] = get_next_line(fd);
		if (data->map[i])
		{		
			len = ft_strlen(data->map[i]);
			if (data->map[i][len - 1] == '\n')
				data->map[i][len - 1] = 0;
		}
	}
	return (0);
}
void	init_game(t_data *data)
{
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);//TODO a enlever pour downgrade
	data->ray.pos.x = (double)data->player.pos_y / MINITILES + (0.5);
	data->ray.pos.y = (double)data->player.pos_x / MINITILES + (0.5);
	data->ray.cam_x = 0;
	data->ray.side_dist.x = 0;
	data->ray.side_dist.y = 0;
	data->ray.delta_dist.x = 0;
	data->ray.delta_dist.y = 0;
	data->ray.step.x = 1;
	data->ray.step.y = 1;
	data->ray.cam_angle = 0.5;
}
