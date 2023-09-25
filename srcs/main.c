/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:57:57 by emlamoth          #+#    #+#             */
/*   Updated: 2023/09/25 15:26:04 by emlamoth         ###   ########.fr       */
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

int is_collision(t_data *data, int playerX, int playerY, int playerRadius)
{
// write(1, "test1\n", 5);
	int	gridX;
	int	gridY;
	int	dx;
	int	dy;
	int	squaredDist;
	int	maxSquaredDist;
	// Convert player's pixel coordinates to grid coordinates
	gridX = playerX / MINITILES;
	gridY = playerY / MINITILES;

	// Check if the player's grid cell contains a wall ('1')
	// write(1, "test2\n", 5);
	if (data->map[gridY] && data->map[gridY][gridX] == '1')
	{
		dx = playerX - (gridX * MINITILES + MINITILES / 2);
		dy = playerY - (gridY * MINITILES + MINITILES / 2);
		squaredDist = dx * dx + dy * dy;

		// Calculate the maximum squared distance allowed for collision
		maxSquaredDist = (playerRadius + MINITILES / 2) * (playerRadius + MINITILES / 2);

		// Collision detected if the squared distance is less than or equal to the allowed maximum
		return (squaredDist <= maxSquaredDist);
	}

	// No collision
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

	// Convert playerAngle from degrees to radians
	angleRad = playerAngle * DEGRE;
	// Calculate the endpoint coordinates
	lineLength = 100;
	lineEndX = playerX + (int)(lineLength * cos(angleRad));
	lineEndY = playerY + (int)(lineLength * sin(angleRad));
	lineEndRadius = 15;
	// printf("lineendx = %i\n", lineEndX);
	// printf("lineendy = %i\n", lineEndY);

	// Step size for drawing the line
	int step = 1;

	// Determine the direction of the line (positive or negative step)
	if (lineEndX < playerX)
		step = -1;
	// Calculate the slope of the line
	slope = (float)(lineEndY - playerY) / (float)(lineEndX - playerX);

	x = playerX;
	y = playerY;

	while ((step ==  1 && x <= lineEndX) || (step == -1 && x >= lineEndX))
	{
		// if (x < 0 || x > 1023 || y < 0 || y > 767)
		// {	
		// 	ft_printf("ALLO\n");
		// 	break; // Stop drawing if outside boundaries
		// }
		// Check for collision at the current position
		if (is_collision(data, x, y, lineEndRadius)) // Assuming playerRadius is 10 for collision check
			break; // Stop drawing if a collision is detected

		// Check if the current position is outside the minimap boundaries


		// Draw the pixel at the current position
		if (x >= 0 && x < WINWIDTH && y >= 0 && y < WINHEIGHT)
			mlx_put_pixel(image, x, y, color);
		else
			return ;
		// Calculate the next position
		x += step;
		y = playerY + (int)(slope * (x - playerX));
	}

	step = 1;

	// Determine the direction of the line (positive or negative step)
	if (lineEndY < playerY)
		step = -1;

	// Calculate the slope of the line
	slope = (float)(lineEndX - playerX) / (float)(lineEndY - playerY);

	x = playerX;
	y = playerY;


	while ((step ==  1 && y <= lineEndY) || (step == -1 && y >= lineEndY))
	{
		// if (x < 0 || x > 1023 || y < 0 || y > 767)
		// {	
		// 	ft_printf("ALLO2\n");
		// 	break; // Stop drawing if outside boundaries
		// }
		// Check for collision at the current position
		if (is_collision(data, x, y, lineEndRadius)) // Assuming playerRadius is 10 for collision check
		{
			break; // Stop drawing if a collision is detected
		}

		// Check if the current position is outside the minimap boundaries


		// Draw the pixel at the current position
		if (x >= 0 && x < WINWIDTH && y >= 0 && y < WINHEIGHT)
			mlx_put_pixel(image, x, y, color);
		else
			return ;

		// Calculate the next position
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
	numRays = WINWIDTH;
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
		i++;
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
	int pix_y = 0;
	
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
	t_data *data;
	data = param;
	(void) data;
	int playerRadius = 10;

	draw_minimap(data->image.minimap, data->map);
	draw_filled_circle(data->image.minimap, data->player.pos_x, data->player.pos_y, playerRadius, 0x0000FFFF);
	draw_raycast_on_minimap(data, data->image.minimap, data->player.pos_x, data->player.pos_y);
	// printf("%f\n", data->angle);
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
	data.angle = 180;
	data.mlx = mlx_init(WINWIDTH, WINHEIGHT, "cub3D", 0);
	data.image.minimap = mlx_new_image(data.mlx, WINWIDTH, WINHEIGHT);
	mlx_image_to_window(data.mlx, data.image.minimap, 0, 0);
	// mlx_image_to_window(data.mlx, data.image.miniplayer, 0, 0);
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_loop(data.mlx);
	// mlx_delete_image(data.mlx, data.image.east);
	// mlx_delete_texture(data.texture.east);
	mlx_terminate(data.mlx);
	ft_freeall(data.map);
}