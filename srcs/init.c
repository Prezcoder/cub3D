/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:54:57 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/05 08:56:38 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_data	*init_data(t_data *data, char **argv)
{
	if(!argv)
		return(data);
	ft_bzero(data, sizeof(t_data));
	data->player.map_x = -1;
	data->player.map_y = -1;
	return(data);
}

int	init_map(t_data *data, char *path)
{
	int		fd;
	int		i;
	int		len;
	char	*temp;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return(errhandler(ERRMAP));
	temp = get_next_line(fd);
	while(temp)
	{
		ft_freenull(&temp);
		temp = get_next_line(fd);
		i++;
	}
	data->param.nbline = i;
	close(fd);
	data->map = ft_calloc(i + 1, sizeof(char *));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return(errhandler(ERRMAP));
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
	//--------print la map-------//
	// i = 0;
	// while(data->map[i])
	// 	ft_printf("%s", data->map[i++]);
	return(0);
}
