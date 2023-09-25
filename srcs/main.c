/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:57:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/09/25 08:33:16 by fbouchar         ###   ########.fr       */
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
		data->image.miniplayer->instances[0].y -= 2.5;
		// ft_printf("w");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->image.miniplayer->instances[0].x -= 2.5;
		// ft_printf("a");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->image.miniplayer->instances[0].y += 2.5;
		// ft_printf("s");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->image.miniplayer->instances[0].x += 2.5;
		// ft_printf("d");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->angle += 2.5;
		if(data->angle >= 360)
			data->angle -= 360;
		// ft_printf("(RIGHT)");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->angle -= 2.5;
		if(data->angle < 0)
			data->angle += 360;
		// ft_printf("(LEFT)");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		// ft_printf("(ESCAPE)");
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
	else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (data->image.minifloor);
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
	make_tiles(data->image.minifloor, 0x18DA47FF, MINITILES);
	make_tiles(data->image.miniwall, 0x744603FF, MINITILES);
	make_tiles(data->image.miniplayer, 0xDFB155FF, MINITILES / 2);
}

// void	drawline(t_image *image, t_coor start, t_coor end, u_int32_t color)
// {
// 	int i;
// 	int	dx;
// 	int	dy;

// 	dx = end.x - start.x;
// 	dy = end.y - start.y;
// 	abs
	
// 	while(i--)
// 	{
// 		mlx_put_pixel();
// 	}
// }
void	ft_img_to_win(t_data *data)
{
	int	x;
	int	y;
	mlx_image_t *temp_img;
	
	y = data->player.start_map;
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
					temp_img, x * MINITILES, y * MINITILES);
			}
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, data->image.miniplayer, data->player.pos_x , data->player.pos_y);
}

void	render(void *param)
{
	// double pos_x;
	// double pos_y;
	t_data *data;
	data = param;
	(void) data;
	mlx_delete_image(data->mlx, data->image.window);
	data->image.window = mlx_new_image(data->mlx, WINWIDTH, WINHEIGHT);
	dda_algorithm(data, data->image.miniplayer->instances->x + (MINITILES / 4), data->image.miniplayer->instances->y + (MINITILES / 4), data->image.window);
	mlx_image_to_window(data->mlx, data->image.window, 0, 0);
	// printf("W %d\n", data->image.miniwall->count);
	// printf("F %d\n", data->image.minifloor->count);
	// printf("WIN %d\n", data->image.window->count);
	// printf("P %d\n", data->image.miniplayer->count);
}
int main(int argc, char **argv)
{	t_data data;

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
	data.mlx = mlx_init(WINWIDTH, WINHEIGHT, "cub3D", 0);
	data.image.window = mlx_new_image(data.mlx, WINWIDTH, WINHEIGHT);
	
	ft_img_to_win(&data);
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_loop(data.mlx);
	// mlx_delete_image(data.mlx, data.image.east);
	// mlx_delete_texture(data.texture.east);
	mlx_terminate(data.mlx);
	ft_freeall(data.map);
}