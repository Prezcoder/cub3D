/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:57:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/09/07 17:46:11 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	errhandler(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	return(-1);
}

t_data	*init_data(t_data *data, char **argv)
{
	if(!argv)
		return(data);
	return(data);
}

void	init_map(t_data *data, char *path)
{
	int fd;
	int i;
	char *temp;

	i = 0;
	(void) data;
	fd = open(path, O_RDONLY);
	temp = get_next_line(fd);
	while(temp)
	{
		ft_freenull(&temp);
		temp = get_next_line(fd);
		i++;
	}	
	close(fd);
	data->map = ft_calloc(i + 1, sizeof(char *));
	fd = open(path, O_RDONLY);
	i = 0;
	data->map[i] = get_next_line(fd);
	while(data->map[i++])
		data->map[i] = get_next_line(fd);
	i = 0;
	while(data->map[i])
		ft_printf("%s", data->map[i++]);
}

int main(int argc, char **argv)
{
	t_data data;
	
	if(argc != 2)
		return(errhandler(ERRARGC));
	init_data(&data, argv);
	init_map(&data, argv[1]);
	data.mlx = mlx_init(WINWIDTH, WINHEIGHT, "cub3D", 0);
	data.texture.east = mlx_load_png(TEMPMAP);
	data.image.east = mlx_texture_to_image(data.mlx, data.texture.east);
	mlx_image_to_window(data.mlx, data.image.east, 0, 0);
	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.image.east);
	mlx_delete_texture(data.texture.east);
	mlx_terminate(data.mlx);
	ft_freeall(data.map);
}