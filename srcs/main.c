/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:57:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/10/10 11:17:18 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	ft_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	errhandler(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	return(-1);
}

void	center_dot(mlx_image_t *image)
{
	int x;
	int y;
	int dx;
	int dy;
	int radius = 3;
	
	x = (WINWIDTH / 2) - radius;
	while (x <= (WINWIDTH / 2) + radius)
	{
		y = (WINHEIGHT / 2) - radius;
		while (y <= (WINHEIGHT / 2) + radius)
		{
			dx = x - (WINWIDTH / 2);
			dy = y - (WINHEIGHT / 2);
			if (dx * dx + dy * dy <= radius * radius)
			{
				mlx_put_pixel(image, x, y, 0xFFFFFFFF);
			}
			y++;
		}
		x++;
	}
}
int	main(int argc, char **argv)
{
	t_data	data;
	char	**map_temp;
	
	if (argc != 2)
		return(errhandler(ERRARGC));
	if (ft_strlen(argv[1]) < 12)
		return (ft_printf("Error\nThe file format isn't good.\n"));
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		return (ft_printf("Error\nThe file format isn't good.\n"));
	init_data(&data, argv);
	if (init_map(&data, argv[1]) == -1)
		return(-1);
	parsing(&data);
	wall_check(&data);
	map_temp = ft_tabdup(&(data.map[data.player.start_map]));
	ft_freeall(data.map);
	data.map = map_temp;
	data.mlx = mlx_init(WINWIDTH, WINHEIGHT, "cub3D", 0);
	init_texture(&data);
	// mouse_init(&data);
	data.image.window = mlx_new_image(data.mlx, WINWIDTH, WINHEIGHT);
	mlx_image_to_window(data.mlx, data.image.window, 0, 0);
	// data.image.minimap = mlx_new_image(data.mlx, WINWIDTH, WINHEIGHT);
	// mlx_image_to_window(data.mlx, data.image.minimap, 0, 0);
	// mlx_key_hook(data.mlx, &key_hook, &data);
	//-------------------------------------
	// mlx_loop_hook(data.mlx, &render, &data);
	//-----------------------------
	
	init_game(&data);
	mlx_loop_hook(data.mlx, &loop, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	ft_freeall(data.map);
}

//TODO pourquoi faut diviser player.pos par MINITILES
