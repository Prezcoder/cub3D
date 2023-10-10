/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nic_a_seg_fault.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:03:50 by emlamoth          #+#    #+#             */
/*   Updated: 2023/10/10 11:05:38 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_collision(t_data *data, int playerX, int playerY, int playerRadius)
{
	(void)playerRadius;
	int	gridX;
	int	gridY;
	
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
	t_data *data;
	(void) keydata;

	data = param;
	float angleRad;
	int playerRadius;
	float moveSpeed;
	int newX;
	int newY;
	
	playerRadius = 5;
	moveSpeed = 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		angleRad = data->angle * DEGRE;
		newX = data->player.pos_x + (int)(moveSpeed * cos(angleRad));
		newY = data->player.pos_y + (int)(moveSpeed * sin(angleRad));
		if (!is_collision(data, newX, newY, playerRadius))
		{
			data->player.pos_x = newX;
			data->player.pos_y = newY;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		angleRad = data->angle * DEGRE;
        newX = data->player.pos_x - (int)(moveSpeed * cos(angleRad));
        newY = data->player.pos_y - (int)(moveSpeed * sin(angleRad));
        if (!is_collision(data, newX, newY, playerRadius))
        {
            data->player.pos_x = newX;
            data->player.pos_y = newY;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        angleRad = (data->angle - 90.0) * DEGRE;
        newX = data->player.pos_x + (int)(moveSpeed * cos(angleRad));
        newY = data->player.pos_y + (int)(moveSpeed * sin(angleRad));
        if (!is_collision(data, newX, newY, playerRadius))
        {
            data->player.pos_x = newX;
            data->player.pos_y = newY;
        }
    }
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
		angleRad = (data->angle + 90.0) * DEGRE;
		newX = data->player.pos_x + (int)(moveSpeed * cos(angleRad));
		newY = data->player.pos_y + (int)(moveSpeed * sin(angleRad));
		if (!is_collision(data, newX, newY, playerRadius))
		{
			data->player.pos_x = newX;
			data->player.pos_y = newY;
		}
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->angle += 10;
		if(data->angle >= 360)
			data->angle -= 360;
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->angle -= 10;
		if(data->angle <= 0)
			data->angle += 360;
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if(mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

void	draw_line_from_angle_stop_on_collision2(t_data *data, mlx_image_t *image, int playerX, int playerY, float playerAngle, uint32_t color)
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
	lineLength = 15;
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

void	draw_raycast_on_minimap(t_data *data, mlx_image_t *image, int playerX, int playerY)
{
	int		numRays;
	int		fovAngle;
	float	angleIncrement;
	float	startAngle;
	float	currentAngle;
	int		i;

	i = 0;
	numRays = 60;
	fovAngle = 60;
	angleIncrement = (float)fovAngle / (float)(numRays - 1);
	startAngle = data->angle - (float)(fovAngle / 2);
	while (i < numRays)
	{
		currentAngle = startAngle + i * angleIncrement;
		draw_line_from_angle_stop_on_collision2(data, image, playerX, playerY, currentAngle,ft_color(255,0,0,255));
		i += 2;
	}
}

void	draw_filled_circle(mlx_image_t *image, int centerX, int centerY, int radius, uint32_t color)
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
	// (void) data;
	// int playerRadius = 5;
	// draw_minimap(data->image.minimap, data->map);
	// draw_filled_circle(data->image.minimap, data->player.pos_x, data->player.pos_y, playerRadius, 0x0000FFFF);
	// draw_raycast_on_minimap(data, data->image.minimap, data->player.pos_x, data->player.pos_y);
	// dda_algorithm(data, data->player.pos_x, data->player.pos_y, data->image.minimap);
	// printf("%f\n", data->angle);
}