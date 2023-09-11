/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:57:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/09/11 12:04:40 by emman            ###   ########.fr       */
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

int	init_map(t_data *data, char *path)
{
	int fd;
	int i;
	char *temp;

	i = 0;
	(void) data;
	fd = open(path, O_RDONLY);
	if(fd == -1)
		return(errhandler(ERRMAP));
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
	if(fd == -1)
		return(errhandler(ERRMAP));
	i = 0;
	data->map[i] = get_next_line(fd);
	while(data->map[i++])
		data->map[i] = get_next_line(fd);
	//--------print la map-------//
	i = 0;
	while(data->map[i])
		ft_printf("%s", data->map[i++]);
	return(0);
}
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data *data;
	(void) keydata;
	data = param;
	if(mlx_is_key_down(data->mlx, MLX_KEY_W))
		ft_printf("w");
}

void	render(void *param)
{
	t_data *data;
	data = param;
	uint32_t x;
	uint32_t y;
	
	x = 0;
	y = 0;
	// (void) data;
	while(y < 150)
	{
		x = 0;
		while(x < 150)
		{
			mlx_put_pixel(data->image.east, x, y, (uint32_t)0xFFFF00FF);
			x++;
		}
		y++;
	}
}

int main(int argc, char **argv)
{
	t_data data;

	if(argc != 2)
		return(errhandler(ERRARGC));
	init_data(&data, argv);
	//if(init_map(&data, argv[1]) == -1)
	//	return(-1);
	data.mlx = mlx_init(WINWIDTH, WINHEIGHT, "cub3D", 0);
	// image1 = mlx_new_image(data.mlx, 50, 50);

	// data.texture.east = mlx_load_png(TEMPMAP);
	// data.image.east = mlx_texture_to_image(data.mlx, data.texture.east);
	// mlx_new_image()
	data.image.east = mlx_new_image(data.mlx, 100, 100);
	mlx_image_to_window(data.mlx, data.image.east, 0, 0);
	// mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_loop(data.mlx);
	// mlx_delete_image(data.mlx, data.image.east);
	// mlx_delete_texture(data.texture.east);
	mlx_terminate(data.mlx);
	// ft_freeall(data.map);
}