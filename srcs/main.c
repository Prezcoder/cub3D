/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:57:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/09/27 09:57:36 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t ft_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	errhandler(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	return(-1);
}

// int is_collision(t_data *data, int playerX, int playerY, int playerRadius)
// {
// 	int	gridX;
// 	int	gridY;
// 	int	dx;
// 	int	dy;
// 	int	squaredDist;
// 	int	maxSquaredDist;

// 	gridX = playerX / MINITILES;
// 	gridY = playerY / MINITILES;
// 	if (data->map[gridY] && data->map[gridY][gridX] == '1')
// 	{
// 		dx = playerX - (gridX * MINITILES + MINITILES / 2);
// 		dy = playerY - (gridY * MINITILES + MINITILES / 2);
// 		squaredDist = dx * dx + dy * dy;
// 		maxSquaredDist = (playerRadius + MINITILES / 2) * (playerRadius + MINITILES / 2);
// 		return (squaredDist <= maxSquaredDist);
// 	}
// 	return (0);
// }

int is_collision(t_data *data, int playerX, int playerY, int playerRadius)
{
	(void)playerRadius;
	int gridX;
	int gridY;
	
	gridX = playerX / MINITILES;
	gridY = playerY / MINITILES;
	// TODO ajuster
	if (gridX >= 0 && gridX < 25 && gridY >= 0 && gridY < 7)
		if (data->map[gridY] && data->map[gridY][gridX] == '1')
			return (1);
	return (0);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	// int movespeed = 4;
	t_data *data;
	(void) keydata;

	data = param;
	int playerRadius = 5;
    float moveSpeed = 4.0; // Adjust the movement speed as needed

    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        // Calculate the new position based on the player's angle
        float angleRad = data->angle * DEGRE;
        int newX = data->player.pos_x + (int)(moveSpeed * cos(angleRad));
        int newY = data->player.pos_y + (int)(moveSpeed * sin(angleRad));

        // Check for collision before updating the position
        if (!is_collision(data, newX, newY, playerRadius))
        {
            data->player.pos_x = newX;
            data->player.pos_y = newY;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        // Calculate the new position based on the player's angle
        float angleRad = data->angle * DEGRE;
        int newX = data->player.pos_x - (int)(moveSpeed * cos(angleRad));
        int newY = data->player.pos_y - (int)(moveSpeed * sin(angleRad));

        // Check for collision before updating the position
        if (!is_collision(data, newX, newY, playerRadius))
        {
            data->player.pos_x = newX;
            data->player.pos_y = newY;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        // Calculate the new position based on the player's angle - 90 degrees
        float angleRad = (data->angle - 90.0) * DEGRE;
        int newX = data->player.pos_x + (int)(moveSpeed * cos(angleRad));
        int newY = data->player.pos_y + (int)(moveSpeed * sin(angleRad));

        // Check for collision before updating the position
        if (!is_collision(data, newX, newY, playerRadius))
        {
            data->player.pos_x = newX;
            data->player.pos_y = newY;
        }
    }
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        // Calculate the new position based on the player's angle + 90 degrees
        float angleRad = (data->angle + 90.0) * DEGRE;
        int newX = data->player.pos_x + (int)(moveSpeed * cos(angleRad));
        int newY = data->player.pos_y + (int)(moveSpeed * sin(angleRad));

        // Check for collision before updating the position
        if (!is_collision(data, newX, newY, playerRadius))
        {
            data->player.pos_x = newX;
            data->player.pos_y = newY;
        }
    }

	if(mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->angle += 6.5;
		if(data->angle >= 360)
			data->angle -= 360;
		// ft_printf("(RIGHT)");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->angle -= 6.5;
		if(data->angle <= 0)
			data->angle += 360;
		// ft_printf("(LEFT)");
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		// ft_printf("(ESCAPE)");
		mlx_close_window(data->mlx);
	}
}

void draw_line_from_angle_stop_on_collision2(t_data *data, mlx_image_t *image, int playerX, int playerY, float playerAngle, uint32_t color)
{
	int x;
	int y;
	float lineEndRadius;
	int lineLength;
	float angleRad;
	int lineEndX;
	int lineEndY;
	float slope;
	(void)image;
	(void)color;

	angleRad = playerAngle * DEGRE;
	lineLength = 12;
	lineEndX = playerX + (int)(lineLength * cos(angleRad));
	lineEndY = playerY + (int)(lineLength * sin(angleRad));
	lineEndRadius = 15;
	int step = 1;
	if (lineEndX < playerX)
		step = -1;
	slope = (float)(lineEndY - playerY) / (float)(lineEndX - playerX);

	x = playerX;
	y = playerY;

	while ((step ==  1 && x < lineEndX) || (step == -1 && x > lineEndX))
	{
		// TODO changer largeur et hauteur
		if (x >= 0 && x < WINWIDTH && y >= 0 && y < 224)
		{
			if (is_collision(data, x, y, lineEndRadius))
				break;
			mlx_put_pixel(image, x, y, color);
		}
		else
			break ;
		x += step;
		y = playerY + (int)(slope * (x - playerX));
	}
	step = 1;
	if (lineEndY < playerY)
		step = -1;
	slope = (float)(lineEndX - playerX) / (float)(lineEndY - playerY);
	x = playerX;
	y = playerY;
	while ((step ==  1 && y < lineEndY) || (step == -1 && y > lineEndY))
	{
		if (x >= 0 && x < WINWIDTH && y >= 0 && y < 224)
		{
			if (is_collision(data, x, y, lineEndRadius))
				break;
			mlx_put_pixel(image, x, y, color);
		}
		else
			break ;
		y += step;
		x = playerX + (int)(slope * (y - playerY));
	}
}

void draw_raycast_on_minimap(t_data *data, mlx_image_t *image, int playerX, int playerY)
{
	int		numRays; // Adjust the number of rays as needed
	int		fovAngle; // Adjust the field of view angle as needed
	float	angleIncrement;
	float	startAngle;
	float	currentAngle;
	int		i;

	i = 0;
	numRays = 60;
	fovAngle = 60;
	angleIncrement = (float)fovAngle / (float)(numRays - 1);
	startAngle = data->angle - (float)(fovAngle / 2);

	// Iterate over the number of rays
	while (i < numRays)
	{
		// Calculate the angle for the current ray
		currentAngle = startAngle + i * angleIncrement;
		// Call draw_line_from_angle_stop_on_collision for the current ray
		draw_line_from_angle_stop_on_collision2(data, image, playerX, playerY, currentAngle,ft_color(255,0,0,255));
		i += 2;
	}
}

void draw_filled_circle(mlx_image_t *image, int centerX, int centerY, int radius, uint32_t color)
{
	int x;
	int y;
	int dx;
	int dy;
	
	x = centerX - radius;
	while (x <= centerX + radius)
	{
		y = centerY - radius;
		while (y <= centerY + radius)
		{
			dx = x - centerX;
			dy = y - centerY;
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
	int pix_y;
	
	pix_y = 0;
	while(map[pix_y / MINITILES] && pix_y < WINHEIGHT)
	{
		pix_x = 0;
		while(map[pix_y / MINITILES][pix_x / MINITILES] && pix_x < WINWIDTH)
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
	// double pos_x;
	// double pos_y;
	t_data *data;
	data = param;
	(void) data;
	int playerRadius = 5;

	draw_minimap(data->image.minimap, data->map);
	draw_filled_circle(data->image.minimap, data->player.pos_x, data->player.pos_y, playerRadius, 0x0000FFFF);
	draw_raycast_on_minimap(data, data->image.minimap, data->player.pos_x, data->player.pos_y);
	// dda_algorithm(data, data->player.pos_x, data->player.pos_y, data->image.minimap);
	// printf("%f\n", data->angle);
}

int main(int argc, char **argv)
{
	t_data data;

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
	data.angle = 270;
	data.mlx = mlx_init(WINWIDTH, WINHEIGHT, "cub3D", 0);
	data.image.window = mlx_new_image(data.mlx, WINWIDTH, WINHEIGHT);
	mlx_image_to_window(data.mlx, data.image.window, 0, 0);
	// data.image.minimap = mlx_new_image(data.mlx, WINWIDTH, WINHEIGHT);
	// mlx_image_to_window(data.mlx, data.image.minimap, 0, 0);
	// mlx_key_hook(data.mlx, &key_hook, &data);
	// mlx_loop_hook(data.mlx, &render, &data);
	init_game(&data);
	mlx_loop_hook(data.mlx, &loop, &data);
	mlx_loop(data.mlx);
	// mlx_delete_image(data.mlx, data.image.east);
	// mlx_delete_texture(data.texture.east);
	mlx_terminate(data.mlx);
	ft_freeall(data.map);
}