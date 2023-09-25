/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:57:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/09/25 12:25:56 by emlamoth         ###   ########.fr       */
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
	int movespeed = 4;
	t_data *data;
	(void) keydata;

	data = param;
	if(mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->player.pos_y -= movespeed;
		// ft_printf("w");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->player.pos_x -= movespeed;
		// ft_printf("a");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->player.pos_y += movespeed;
		// ft_printf("s");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->player.pos_x += movespeed;
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

void draw_filled_circle(mlx_image_t *image, int centerX, int centerY, int radius, uint32_t color)
{
    int x = centerX - radius;
    while (x <= centerX + radius)
    {
        int y = centerY - radius;
        while (y <= centerY + radius)
        {
            int dx = x - centerX;
            int dy = y - centerY;
            if (dx * dx + dy * dy <= radius * radius)
            {
                mlx_put_pixel(image, x, y, color);
            }
            y++;
        }
        x++;
    }
}

void	draw_minimap(mlx_image_t *image, char **map)
{
	int pix_x;
	int pix_y = 0;
	
	pix_y = 0;
	while(map[pix_y / MINITILES])
	{
		pix_x = 0;
		while(map[pix_y / MINITILES][pix_x / MINITILES])
		{
			if(map[pix_y / MINITILES][pix_x / MINITILES] == '1')
				mlx_put_pixel(image, pix_x, pix_y, 0x000000FF);
			else
				mlx_put_pixel(image, pix_x, pix_y, 0x00FF00FF);
			pix_x++;
		}
		pix_y++;
	}
}

void	render(void *param)
{
	t_data *data;
	data = param;
	(void) data;
	int playerRadius = 10;

	draw_minimap(data->image.minimap, data->map);
	draw_filled_circle(data->image.minimap, data->player.pos_x + (MINITILES / 4), data->player.pos_y + (MINITILES / 4), playerRadius, 0x0000FFFF);

}

int main(int argc, char **argv)
{	t_data data;

	char **map_temp;
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
	map_temp = ft_tabdup(&data.map[data.player.start_map]);
    ft_freeall(data.map);
    data.map = map_temp;
	data.mlx = mlx_init(WINWIDTH, WINHEIGHT, "cub3D", 0);
	data.image.minimap = mlx_new_image(data.mlx, WINWIDTH, WINHEIGHT);
	mlx_image_to_window(data.mlx, data.image.minimap, 0, 100);
	// mlx_image_to_window(data.mlx, data.image.miniplayer, 0, 0);
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_loop(data.mlx);
	// mlx_delete_image(data.mlx, data.image.east);
	// mlx_delete_texture(data.texture.east);
	mlx_terminate(data.mlx);
	ft_freeall(data.map);
}