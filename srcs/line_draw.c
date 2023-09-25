/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 08:34:04 by fbouchar          #+#    #+#             */
/*   Updated: 2023/09/25 10:10:18 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int scaleFactor = 40;
mlx_image_t *map;

uint32_t ft_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

double deg_to_rad(double degree)
{
    // Convert playerAngle from degrees to radians
    return (degree * M_PI / 180.0);
}

//put black pixel everywhere
void reset_window(mlx_image_t *image)
{
    for (int x = 0; x < WINWIDTH; x++)
    {
        for (int y = 0; y < WINHEIGHT; y++)
        {
            mlx_put_pixel(image, x, y, ft_color(0, 0, 0, 255)); // Set pixel to black
        }
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

int is_collision(t_data *data, int playerX, int playerY, int playerRadius)
{
    // Convert player's pixel coordinates to grid coordinates
    int gridX = playerX / scaleFactor;
    int gridY = playerY / scaleFactor;

    // Check if the player's grid cell contains a wall ('1')
    if (data->map[gridY][gridX] == '1')
    {
        // Calculate the squared distance from the player's center to the cell center
        int dx = playerX - (gridX * scaleFactor + scaleFactor / 2);
        int dy = playerY - (gridY * scaleFactor + scaleFactor / 2);
        int squaredDist = dx * dx + dy * dy;

        // Calculate the maximum squared distance allowed for collision
        int maxSquaredDist = (playerRadius + scaleFactor / 2) * (playerRadius + scaleFactor / 2);

        // Collision detected if the squared distance is less than or equal to the allowed maximum
        return squaredDist <= maxSquaredDist;
    }

    // No collision
    return 0;
}



/////SUUSPECTE TO CAUSE THE SEGFAULT IN #D PERSPECTIVE WHEN TOO CLOSE TO WALL***
float calculate_wall_distance(t_data *data, int playerX, int playerY, float rayAngle)
{
    // Constants
    const float rayStepSize = 0.1;   // Step size for ray casting
    const float maxDistance = 5000.0; // Maximum raycasting distance

    // Convert rayAngle from degrees to radians
    float angleRad = deg_to_rad(rayAngle);

    float rayX = playerX;
    float rayY = playerY;

    while (rayX >= 0 && rayX < WINWIDTH && rayY >= 0 && rayY < WINHEIGHT)
    {
        // Calculate the grid coordinates of the current cell
        int gridX = (int)(rayX / scaleFactor);
        int gridY = (int)(rayY / scaleFactor);

        // Check if the current cell is within bounds
        if (gridX >= 0 && gridX < WINWIDTH && gridY >= 0 && gridY < WINHEIGHT)
        {
            // Check if the current cell is a wall ('1')
            if (data->map[gridY][gridX] == '1')
            {
                // Calculate the distance to the wall using the Pythagorean theorem
                float dx = rayX - playerX;
                float dy = rayY - playerY;

                // Ensure dx and dy are positive
                if (dx < 0) dx = -dx;
                if (dy < 0) dy = -dy;

                return sqrt(dx * dx + dy * dy);
            }
        }

        // Move to the next position along the ray
        rayX += rayStepSize * cos(angleRad);
        rayY += rayStepSize * sin(angleRad);

        // Limit the maximum raycasting distance to avoid infinite loops
        if (rayX - playerX >= maxDistance || rayY - playerY >= maxDistance)
        {
            break;
        }
    }

    // If the ray reaches the edge of the map or the maximum distance, return -1
    return -1.0;
}





void draw_field_of_view(t_data *data, mlx_image_t *image, int playerX, int playerY)
{
    // Define FOV and other constants
    float fov = 90.0; // Field of view angle in degrees
    int numRays = WINWIDTH; // Number of rays (one per pixel)
    float rayAngleIncrement = fov / numRays;

    // Calculate the starting angle for the FOV
    float startAngle = data->player.angle - (fov / 2);

    // Iterate over the entire FOV and cast rays
    for (int wallX = 0; wallX < WINWIDTH; wallX++)
    {
        // Calculate the angle for the current ray
        float rayAngle = startAngle + wallX * rayAngleIncrement;
        rayAngle = fmod(rayAngle, 360.0); // Ensure the angle is within [0, 360)

        // Use rayAngle to calculate the distance to the wall
        float distance = calculate_wall_distance(data, playerX, playerY, rayAngle);
        if(distance < 1)
        distance = 1;

        // Calculate the height of the wall based on its distance for perspective
        int wallHeight = (int)(WINHEIGHT / distance) * (cos((startAngle-wallX) - data->player.angle)) * 5;

        // Calculate the Y-coordinates for the top and bottom of the wall segment
        int wallTop = (WINHEIGHT - wallHeight) / 2;
        if(wallTop > WINHEIGHT)
        wallTop = WINHEIGHT;
        int wallBottom = wallTop + wallHeight;
        if(wallBottom < 0)
        wallBottom = 0;

        // Draw the wall segment on the screen as a vertical line
        for (int y = wallTop; y < wallBottom; y++ )
        {
            mlx_put_pixel(image, wallX, y, ft_color(0, 255, 0, 255)); // Set color for the wall
        }
    }
}




void draw_line_from_angle_stop_on_collision2(t_data *data, mlx_image_t *image, int playerX, int playerY, float playerAngle, uint32_t color)
{

    float lineEndRadius =10;
    int lineLength = 1000;
    
    // Convert playerAngle from degrees to radians
    float angleRad = playerAngle * M_PI / 180.0;

    // Calculate the endpoint coordinates
    int lineEndX = playerX + (int)(lineLength * cos(angleRad));
    int lineEndY = playerY + (int)(lineLength * sin(angleRad));


printf("lineendx = %i\n", lineEndX);
printf("lineendy = %i\n", lineEndY);
 
    // Step size for drawing the line
    int step = 1;

    // Determine the direction of the line (positive or negative step)
    if (lineEndX < playerX)
        step = -1;

    // Calculate the slope of the line
    float slope = (float)(lineEndY - playerY) / (float)(lineEndX - playerX);

    int x = playerX;
    int y = playerY;

    while ((step ==  1 && x <= lineEndX) || (step == -1 && x >= lineEndX))
    {
        // Check for collision at the current position
        if (is_collision(data, x, y, lineEndRadius)) // Assuming playerRadius is 10 for collision check
        {
            break; // Stop drawing if a collision is detected
        }

        // Check if the current position is outside the minimap boundaries
        //TODO *****replace 39 and 16 by the value of minimap height and width

        if (x < 0 || x >= 39*scaleFactor || y < 0 || y >= 16*scaleFactor)
        {
            break; // Stop drawing if outside boundaries
        }

        // Draw the pixel at the current position
       mlx_put_pixel(image, x, y, color);

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
        // Check for collision at the current position
        if (is_collision(data, x, y, lineEndRadius)) // Assuming playerRadius is 10 for collision check
        {
            break; // Stop drawing if a collision is detected
        }

        // Check if the current position is outside the minimap boundaries
        //TODO *****replace 39 and 16 by the value of minimap height and width

        if (x < 0 || x >= 39*scaleFactor || y < 0 || y >= 16*scaleFactor)
        {
            break; // Stop drawing if outside boundaries
        }
printf("avant\n");
        // Draw the pixel at the current position
       mlx_put_pixel(image, x, y, color);
printf("apres\n");

        // Calculate the next position
        y += step;
        x = playerX + (int)(slope * (y - playerY));
    }

}

//TODO   sassurer que la representation est fidele au vrai raycast dimpression 
//(celui utiliser dans  la section draw wall de la function draw_field_of_view)
// ((((((utiliser les memes variables))))))

void draw_raycast_on_minimap(t_data *data, mlx_image_t *image, int playerX, int playerY)
{
      // Draw the field of view with rays
    int numRays = WINWIDTH*4; // Adjust the number of rays as needed
    int fovAngle =60; // Adjust the field of view angle as needed
    
    
    // Calculate the angle increment between rays
    float angleIncrement = (float)fovAngle / (float)(numRays - 1);

    // Start angle for the first ray
    float startAngle = data->player.angle - (float)(fovAngle / 2);

    // Iterate over the number of rays
    for (int i = 0; i < numRays; i+=20)
    {
        // Calculate the angle for the current ray
        float currentAngle = startAngle + i * angleIncrement;

        // Call draw_line_from_angle_stop_on_collision for the current ray
        draw_line_from_angle_stop_on_collision2(data, image, playerX, playerY, currentAngle,ft_color(255,0,0,255));
    }
}





void ft_hook(void *param)
{
    // mlx_t *mlx = param;
    t_data *data;

    data = param;
    //reset_pixel
   reset_window(data->image.window);

//draw 3d view
// draw_field_of_view(data, map, data->player.pos_x, data->player.pos_y);



// draw minimap------

    // Original map dimensions (16x39)
    // int originalWidth = 16;
    // int originalHeight = 39;
  printf("%f\n", data->player.angle);

    int i = data->player.start_map;
    while (i < WINWIDTH)
    {
        int j = 0;
        while (j < WINHEIGHT)
        {
            uint32_t color;
            if (data->map[i][j] == '0')
                color = ft_color(255, 255, 255, 255);
            else if (data->map[i][j] == '1')
                color = ft_color(0, 0, 0, 255);
            else
                color = ft_color(0, 0, 0, 100);

// Calculate the pixel coordinates for the current square
            int startX = j * scaleFactor;
            int startY = i * scaleFactor;
            int x = startX;
            while (x < startX + scaleFactor)
            {
                int y = startY;
                while (y < startY + scaleFactor)
                {
                    mlx_put_pixel(data->image.window, x, y, color);
					ft_printf("TEST\n");
                    y++;
                }
                x++;
            }
            j++;
        }
        i++;
    }

// draw player
    int playerRadius = 4; // Adjust the radius as needed
    // draw_filled_circle(data->image.window, data->player.pos_x, data->player.pos_y, playerRadius, ft_color(255, 0, 0, 255));
//draw raycast
    draw_raycast_on_minimap(data, data->image.window, data->player.pos_x, data->player.pos_y);



///-----player_move
    // Handle key presses to update position
    float moveSpeed = 4.0; // Adjust the movement speed as needed

    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        // Calculate the new position based on the player's angle
        float angleRad = deg_to_rad(data->player.angle);
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
        float angleRad = deg_to_rad(data->player.angle);
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
        float angleRad = deg_to_rad(data->player.angle - 90.0);
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
        float angleRad = deg_to_rad(data->player.angle + 90.0);
        int newX = data->player.pos_x + (int)(moveSpeed * cos(angleRad));
        int newY = data->player.pos_y + (int)(moveSpeed * sin(angleRad));

        // Check for collision before updating the position
        if (!is_collision(data, newX, newY, playerRadius))
        {
            data->player.pos_x = newX;
            data->player.pos_y = newY;
        }
    }

    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
        data->player.angle -= 5;
    if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
        data->player.angle += 5;
    if (data->player.angle >= 360)
        data->player.angle = 0;
    if (data->player.angle < 0)
        data->player.angle = 360;
    if(mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(0);
    

}