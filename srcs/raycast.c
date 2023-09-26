/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:02:49 by fbouchar          #+#    #+#             */
/*   Updated: 2023/09/26 18:08:13 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int map[20][20] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

void	init_game(t_data *data)
{
	data->game->pl_pos.x = 2;
	data->game->pl_pos.y = 7;
	data->game->pl_dir.x = 1;
	data->game->pl_dir.y = 0;
	// cam plane
	data->game->plane.y = -0.66;
	data->game->plane.x = 0;

	data->game->cam_x = 0;
	data->game->side_dist.x = 0;
	data->game->side_dist.y = 0;
	data->game->delta_dist.x = 0;
	data->game->delta_dist.y = 0;

	data->game->step.x = 1;
	data->game->step.y = 1;
}

void	set_data(t_data *data)
{
	//set ray dir
	data->game->ray_dir.x = data->game->pl_dir.x + \
		data->game->plane.x * data->game->cam_x;
	data->game->ray_dir.y = data->game->pl_dir.y + \
		data->game->plane.y * data->game->cam_x;
	
	//set map pos
	data->game->coord.x = data->game->pl_pos.x;
	data->game->coord.y = data->game->pl_pos.y;

	//set delta dist
	data->game->delta_dist.x = fabs(1 / data->game->ray_dir.x);
	data->game->delta_dist.y = fabs(1 / data->game->ray_dir.y);
}

void	set_side_dist(t_data *data)
{
	if(data->game->ray_dir.x < 0)
	{
		data->game->step.x = -0.01;
		data->game->side_dist.x = (data->game->pl_pos.x - \
			data->game->coord.x) * data->game->delta_dist.x;
	}
	else
	{
		data->game->step.x = 0.01;
		data->game->side_dist.x = (data->game->coord.x + 1.0 - \
			data->game->pl_pos.x) * data->game->delta_dist.x;
	}
	if(data->game->ray_dir.y < 0)
	{
		data->game->step.y = -0.01;
		data->game->side_dist.y = (data->game->pl_pos.y - \
			data->game->coord.y) * data->game->delta_dist.y;
	}
	else
	{
		data->game->step.y = 0.01;
		data->game->side_dist.y = (data->game->coord.y + 1.0 - \
			data->game->pl_pos.y) * data->game->delta_dist.y;
	}
}

void	dda(t_data *data)
{
	while(1)
	{
		
		if(data->game->side_dist.x < data->game->side_dist.y)
		{
			data->game->side_dist.x += data->game->delta_dist.x;
			data->game->coord.x += data->game->step.x;
			//keep in case of norm too tough on set_side_dist
			// if(data->game->ray_dir.x < 0)
			// 	data->game->coord.x -= 0.01;
			// else
			// 	data->game->coord.x += 0.01;

			data->game->side = 0;
		}
		else
		{
			data->game->side_dist.y += data->game->delta_dist.y;
			data->game->coord.y += data->game->step.y;
			//keep in case of norm too tough on set_side_dist
			// if(data->game->ray_dir.y < 0)
			// 	data->game->coord.y -= 0.01; 
			// else
			// 	data->game->coord.y += 0.01;

			data->game->side = 1;
		}
		if(map[(int)data->game->coord.y][(int)data->game->coord.x])
			break;
	}
	if(data->game->side == 0)
		data->game->perp_wall_dist = (data->game->side_dist.x - data->game->delta_dist.x);
	else
		data->game->perp_wall_dist = (data->game->side_dist.y - data->game->delta_dist.y);
}


void	set_draw_range(t_data *data)
{
	data->game->line_height = (int)((WINHEIGHT * 125) / data->game->perp_wall_dist); //add to add multiply HEIGHT by 125 to smooth mvt
	data->game->draw_start = -data->game->line_height * 0.5 + WINHEIGHT * 0.5;
	if (data->game->draw_start < 0)
		data->game->draw_start = 0;
	data->game->draw_end = data->game->line_height * 0.5 + WINHEIGHT * 0.5;
	if (data->game->draw_end >= WINHEIGHT)
		data->game->draw_end = WINHEIGHT - 1;
}

void	draw_vertline(t_data *data, int x)
{
	int	y;
	
	y = 0;
	printf("%d\n", data->game->draw_end);
	while((int)y < data->game->draw_start)
		mlx_put_pixel(data->image.window, x, y++, ft_color(255, 0, 255, 255)); //ceiling color (Black)
	while((int)y < data->game->draw_end)
		mlx_put_pixel(data->image.window, x, y++, ft_color(255, 255, 0, 255)); // red
	while((int)y < WINHEIGHT)
		mlx_put_pixel(data->image.window, x, y++, ft_color(255, 255, 255, 255)); //floor color (white)
}

void	rotate_vector(double *x, double *y, double angle) 
{
	double old_x ;

	old_x = *x;
	*x = old_x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
}

void	move_player(t_data *data, double move_speed) 
{
   if(map[(int)(data->game->pl_pos.x + data->game->pl_dir.x * move_speed)][(int)data->game->pl_pos.y] == 0)
        data->game->pl_pos.x += data->game->pl_dir.x * move_speed;
    
    // Move along Y direction
    if(map[(int)data->game->pl_pos.x][(int)(data->game->pl_pos.y + data->game->pl_dir.y * move_speed)] == 0)
        data->game->pl_pos.y += data->game->pl_dir.y * move_speed;
}

void strafe_player(t_data *data, double strafe_speed) 
{
    if(map[(int)(data->game->pl_pos.x + data->game->pl_dir.y * strafe_speed)][(int)data->game->pl_pos.y] == 0)
        data->game->pl_pos.x += data->game->pl_dir.y * strafe_speed;
    
    // Strafe along Y direction (perpendicular to direction of facing, so we use -pl_dir.x)
    if(map[(int)data->game->pl_pos.x][(int)(data->game->pl_pos.y - data->game->pl_dir.x * strafe_speed)] == 0)
        data->game->pl_pos.y -= data->game->pl_dir.x * strafe_speed;
}

void	key_binding(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
			mlx_close_window(data->mlx);

	if (mlx_is_key_down(data->mlx, MLX_KEY_W)) 
		move_player(data, MOVE_SPEED); // Move forward
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, -MOVE_SPEED); // Move backward

	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		strafe_player(data, -MOVE_SPEED); // Strafe left
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		strafe_player(data, MOVE_SPEED); // Strafe right

	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)) 
	{
		rotate_vector(&data->game->pl_dir.x, &data->game->pl_dir.y, -ROTATE_SPEED);
		rotate_vector(&data->game->plane.x, &data->game->plane.y, -ROTATE_SPEED);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)) 
	{
		rotate_vector(&data->game->pl_dir.x, &data->game->pl_dir.y, ROTATE_SPEED);
		rotate_vector(&data->game->plane.x, &data->game->plane.y, ROTATE_SPEED);
	}
}
void	loop(void *param)
{
	t_data		*data;
	int	x;

	data = param;
	x = -1;
	while(++x < WINWIDTH)
	{
		data->game->cam_x = 2 * x / (double)WINWIDTH - 1;
		set_data(data);
		set_side_dist(data);
		dda(data);
		set_draw_range(data);
		draw_vertline(data, x);
		key_binding(data);
	}
}
// void	raycast(t_data *data)
// {
// 	double posX = 22, posY = 12;  // x and y start position
// 	double dirX = -1, dirY = 0; // initial direction vector
// 	double planeX = 0, planeY = 0.66; // the 2d raycaster version of camera plane

// 	double time = 0; // time of current frame
// 	double oldTime = 0; // time of previous frame

//     screen(WINWIDTH, WINHEIGHT, 0, "Raycaster");
//     while (1)
// 	{
//         for (int x = 0; x < WINWIDTH; x++) {
//             double cameraX = 2 * x / (double)WINWIDTH - 1; // x-coordinate in camera space
//             double rayDirX = dirX + planeX * cameraX;
//             double rayDirY = dirY + planeY * cameraX;
//             int mapX = (int)posX;
//             int mapY = (int)posY;

//             double sideDistX;
//             double sideDistY;
//             double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//             double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

//             double perpWallDist;

//             int stepX;
//             int stepY;

//             int hit = 0; // was there a wall hit?
//             int side; // was a NS or an EW wall hit?
//             if (rayDirX < 0) {
//                 stepX = -1;
//                 sideDistX = (posX - mapX) * deltaDistX;
//             } else {
//                 stepX = 1;
//                 sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//             }
//             if (rayDirY < 0) {
//                 stepY = -1;
//                 sideDistY = (posY - mapY) * deltaDistY;
//             } else {
//                 stepY = 1;
//                 sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//             }
//             // perform DDA
//             while (hit == 0) {
//                 if (sideDistX < sideDistY) {
//                     sideDistX += deltaDistX;
//                     mapX += stepX;
//                     side = 0;
//                 } else {
//                     sideDistY += deltaDistY;
//                     mapY += stepY;
//                     side = 1;
//                 }
//                 if (data->map[mapX][mapY] > 0) hit = 1;
//             }

//             if (side == 0) perpWallDist = (sideDistX - deltaDistX);
//             else perpWallDist = (sideDistY - deltaDistY);

//             int lineHeight = (int)(WINHEIGHT / perpWallDist);

//             int drawStart = -lineHeight / 2 + WINHEIGHT / 2;
//             if (drawStart < 0) drawStart = 0;
//             int drawEnd = lineHeight / 2 + WINHEIGHT / 2;
//             if (drawEnd >= WINHEIGHT) drawEnd = WINHEIGHT - 1;

//             ColorRGB color;
//             switch (data->map[mapX][mapY]) {
//                 case 1:  color = RGB_Red;    break; // red
//                 case 2:  color = RGB_Green;  break; // green
//                 case 3:  color = RGB_Blue;   break; // blue
//                 case 4:  color = RGB_White;  break; // white
//                 default: color = RGB_Yellow; break; // yellow
//             }
//             if (side == 1) { color = color / 2; }
//             verLine(x, drawStart, drawEnd, color);
//         }
//         oldTime = time;
//         time = getTicks();
//         double frameTime = (time - oldTime) / 1000.0; // frameTime is the time this frame has taken, in seconds

//         double moveSpeed = frameTime * 5.0; // the constant value is in squares/second
//         double rotSpeed = frameTime * 3.0; // the constant value is in radians/second
//         readKeys();
//         if (keyDown(SDLK_UP)) {
//             if (data->map[(int)(posX + dirX * moveSpeed)][(int)posY] == 0) posX += dirX * moveSpeed;
//             if (data->map[(int)posX][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
//         }
//         if (keyDown(SDLK_DOWN)) {
//             if (data->map[(int)(posX - dirX * moveSpeed)][(int)posY] == 0) posX -= dirX * moveSpeed;
//             if (data->map[(int)posX][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
//         }
//         if (keyDown(SDLK_RIGHT)) {
//             double oldDirX = dirX;
//             dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//             dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//             double oldPlaneX = planeX;
//             planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//             planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//         }
//         if (keyDown(SDLK_LEFT)) {
//             double oldDirX = dirX;
//             dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//             dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//             double oldPlaneX = planeX;
//             planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//             planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//         }
//     }
//     return 0;
// }
