/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zmain_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:57:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/10/12 14:27:12 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	free_toute(t_data *data)
{
	system("killall afplay");
	mlx_delete_image(data->mlx, data->image.window);
	mlx_delete_image(data->mlx, data->image.minimap);
	mlx_terminate(data->mlx);
	free_param(data);
	clean_texture(data);
	ft_freeall(data->map);
}

uint32_t	ft_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	errhandler(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	return (-1);
}

void	center_dot(mlx_image_t *image)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	radius;

	radius = 4;
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

	if (argc != 2)
		return (errhandler(ERRARGC));
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		return (errhandler(ERRFORMAT));
	init_data(&data);
	init_map(&data, argv[1]);
	parsing(&data);
	wall_check(&data);
	dup_map(&data);
	data.mlx = mlx_init(WINWIDTH, WINHEIGHT, "cub3D", 0);
	if (!data.mlx)
		cub_exit(&data, ERRMLX);
	init_texture(&data);
	create_windows(&data);
	init_game(&data);
	system("afplay ./music/musique.mp3&");
	mlx_loop_hook(data.mlx, &loop, &data);
	mlx_loop(data.mlx);
	free_toute(&data);
	return (EXIT_SUCCESS);
}
