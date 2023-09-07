/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:57:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/09/07 15:29:56 by emlamoth         ###   ########.fr       */
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

int main(int argc, char **argv)
{
	t_data data;
	
	if(argc != 2)
		return(errhandler(ERRARGC));
	init_data(&data, argv);
	data.mlx = mlx_init(WINWIDTH, WINHEIGHT, "cub3D", 0);
	data.texture.east = mlx_load_png(TEMPMAP);
	data.image.east = mlx_texture_to_image(data.mlx, data.texture.east);
	mlx_image_to_window(data.mlx, data.image.east, 0, 0);
	mlx_loop(data.mlx);
	
}