/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emman <emman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:57:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/09/14 08:40:59 by emman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	errhandler(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	return(-1);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data *data;
	(void) keydata;
	
	data = param;
	if(mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		
		ft_printf("w");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		
		ft_printf("a");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		
		ft_printf("s");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		
		ft_printf("d");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		
		ft_printf("(RIGHT)");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		
		ft_printf("(LEFT)");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		ft_printf("(ESCAPE)");
		mlx_close_window(data->mlx);
	}
}

void	make_tiles(mlx_image_t *square, uint32_t color, int size)
{
	int x;
	int y;
	
	x = 0;
	y = 0;
	while(y < size)
	{
		x = 0;
		while(x < size)
		{
			mlx_put_pixel(square, x, y, color);
			x++;
		}
		y++;
	}
}

mlx_image_t	*ft_set_img(char c, t_data *data)
{
	if (c == '1')
		return (data->image.miniwall);
	else if (c == '0')
		return (data->image.minifloor);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (data->image.miniplayer);
	else if (c == ' ')
		return (NULL);
	else
		exit(1);
}

void	del_old_img(t_data *data)
{
	mlx_delete_image(data->mlx, data->old_image.minifloor);
	mlx_delete_image(data->mlx, data->old_image.miniwall);
	mlx_delete_image(data->mlx, data->old_image.miniplayer);
}

void	mini_image(t_data *data)
{
	data->image.minifloor = mlx_new_image(data->mlx, MINITILES, MINITILES);
	data->image.miniwall = mlx_new_image(data->mlx, MINITILES, MINITILES);
	data->image.miniplayer = mlx_new_image(data->mlx, MINITILES / 2, MINITILES / 2);
	make_tiles(data->image.minifloor, 0xFFFF0030, MINITILES);
	make_tiles(data->image.miniwall, 0xFF00FF30, MINITILES);
	make_tiles(data->image.miniplayer, 0xFF88FFFF, MINITILES / 2);
}

void	ft_img_to_win(t_data *data)
{
	int	x;
	int	y;
	mlx_image_t *temp_img;

	y = 7;
	del_old_img(data);
	data->old_image = data->image;
	mini_image(data);
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x] != '\n' && data->map[y][x])
		{
			temp_img = ft_set_img(data->map[y][x], data);
			if(temp_img)
			{
				mlx_image_to_window(data->mlx,
					temp_img, x * MINITILES + 10, (y * MINITILES) + (WINHEIGHT - (data->param.nbline * MINITILES + 10)));
			}
			x++;
		}
		y++;
	}
}

void	render(void *param)
{
	t_data *data;
	data = param;
	(void) data;
	// mlx_delete_image(data->mlx, data->image.minifloor);
	// mlx_delete_image(data->mlx, data->image.miniwall);

	ft_img_to_win(data);
}
int main(int argc, char **argv)
{	t_data data;

	if(argc != 2)
		return(errhandler(ERRARGC));
	init_data(&data, argv);
	if(init_map(&data, argv[1]) == -1)
		return(-1);
	parsing(&data);
	data.mlx = mlx_init(WINWIDTH, WINHEIGHT, "cub3D", 0);
	// data.image.minifloor = mlx_new_image(data.mlx, 8, 8);
	// data.image.miniwall = mlx_new_image(data.mlx, 8, 8);
	// make_tiles(data.image.minifloor, 0xFFFF0003, 8);
	// make_tiles(data.image.miniwall, 0xFF00FF03, 8);
	// image1 = mlx_new_image(data.mlx, 50, 50);

	// data.texture.east = mlx_load_png(TEMPMAP);
	// data.image.east = mlx_texture_to_image(data.mlx, data.texture.east);
	// mlx_new_image()
	// mlx_image_to_window(data.mlx, data.image.east, 0, 0);
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_loop(data.mlx);
	// mlx_delete_image(data.mlx, data.image.east);
	// mlx_delete_texture(data.texture.east);
	mlx_terminate(data.mlx);
	ft_freeall(data.map);
}