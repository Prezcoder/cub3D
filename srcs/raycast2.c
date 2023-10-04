/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:30:05 by emlamoth          #+#    #+#             */
/*   Updated: 2023/10/04 17:43:47 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void raycast2(t_data *data) 
{
	int x = 0;
	while (x < WINWIDTH)
	{
		draw_vertline(data, x);
		key_binding(data);
		// mouse_tracking(data);
		data->ray.cam_x = 2 * x / (double)WINWIDTH - 1;
		data->ray.ray_dir.x = data->ray.dir.x + data->ray.plane.x * data->ray.cam_x;
		data->ray.ray_dir.y = data->ray.dir.y + data->ray.plane.y * data->ray.cam_x;

		data->ray.coord.x = (int)data->ray.pos.x;
		data->ray.coord.y = (int)data->ray.pos.y;

		data->ray.delta_dist.x = fabs(1 / data->ray.ray_dir.x);
		data->ray.delta_dist.y = fabs(1 / data->ray.ray_dir.y);

		// initialisation des valeurs de sideDistX et sideDistY
		if(data->ray.ray_dir.x < 0)
		{
			data->ray.step.x = -1;
			data->ray.side_dist.x = (data->ray.pos.x - data->ray.coord.x) * data->ray.delta_dist.x;
		}
		else
		{
			data->ray.step.x = 1;
			data->ray.side_dist.x = (data->ray.coord.x + 1.0 - data->ray.pos.x)  * data->ray.delta_dist.x;
		}
		if(data->ray.ray_dir.y < 0)
		{
			data->ray.step.y = -1;
			data->ray.side_dist.y = (data->ray.pos.y - data->ray.coord.y) * data->ray.delta_dist.y;
		}
		else
		{
			data->ray.step.y = 1;
			data->ray.side_dist.y = (data->ray.coord.y + 1.0 - data->ray.pos.y)  * data->ray.delta_dist.y;
		}
		while(42)
		{
			if(data->ray.side_dist.x < data->ray.side_dist.y)
			{
				data->ray.side_dist.x += data->ray.delta_dist.x;
				data->ray.coord.x += data->ray.step.x;
				data->ray.side = 0;
			}
			else
			{
				data->ray.side_dist.y += data->ray.delta_dist.y;
				data->ray.coord.y += data->ray.step.y;
				data->ray.side = 1;
			}
			if(data->map[(int)data->ray.coord.x][(int)data->ray.coord.y] == '1')
				break ;
		}

        // Calcul de la distance du mur au joueur pour éviter la distorsion "fishbowl"
		if(data->ray.side == 0)
			data->ray.perp_wall_dist = (data->ray.coord.x - data->ray.pos.x + (1 - data->ray.step.x) / 2) / data->ray.ray_dir.x;
		else
			data->ray.perp_wall_dist = (data->ray.coord.y - data->ray.pos.y + (1 - data->ray.step.y) / 2) / data->ray.ray_dir.y;

        // Hauteur de la ligne à dessiner
		data->ray.line_height = (int)(WINHEIGHT / data->ray.perp_wall_dist);

        // Calculer les positions de départ et de fin pour dessiner la colonne verticale
		data->ray.draw_start = -data->ray.line_height / 2 + WINHEIGHT / (2 + data->ray.cam_angle);
		if(data->ray.draw_start < 0)
			data->ray.draw_start = 0;
		data->ray.draw_end = data->ray.line_height / 2 + WINHEIGHT / (2 + data->ray.cam_angle);
		if(data->ray.draw_end >= WINHEIGHT)
			data->ray.draw_end = WINHEIGHT - 1;

		// Choix de la texture en fonction de l'orientation du mur
		int texNum;
		if (data->ray.side == 0) 
		{
			if(data->ray.step.x > 0)
				texNum = 0;
			else
				texNum = 1;
		}
		else
		{
			if(data->ray.step.y > 0)
				texNum = 2;
			else
				texNum = 3;
		}
		// Calcul de la valeur de texX
		double	hit;
		if (data->ray.side == 0)
			hit = data->ray.pos.y + data->ray.perp_wall_dist * data->ray.ray_dir.y;
		else
			hit = data->ray.pos.x + data->ray.perp_wall_dist * data->ray.ray_dir.x;
		hit -= (int)hit;
		data->ray.tex_x = (int)(hit * (double)data->textures[texNum]->width);

		// Dessiner la colonne
		int y = data->ray.draw_start;
		while (y < data->ray.draw_end)
		{
			// Calcul de texY

			double def = 1024;// donner qui fait rien d'apparent
			int dist = y * def - WINHEIGHT * (def/2) + data->ray.line_height * (def/2);
			int texY = ((dist * data->textures[texNum]->height) / data->ray.line_height) / def;

			// Obtenez la couleur de la texture
			uint32_t color = *((uint32_t*)data->textures[texNum]->pixels + (texY * data->textures[texNum]->width + data->ray.tex_x));
			uint32_t rearranged_color = ((color & 0xFF000000) >> 24) |  // R
							((color & 0x00FF0000) >> 8)  |  // G
							((color & 0x0000FF00) << 8)  |  // B
							((color & 0x000000FF) << 24);  // A
			// Dessinez le pixel
			mlx_put_pixel(data->image.window, x, y, rearranged_color);

			y++;
		}
		x++;
	}
}
