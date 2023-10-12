/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:02:49 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/12 11:33:15 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	find_hit(t_data *data, mlx_texture_t *texture)
{
	double	hit;

	if (data->texture.door_flag == 1) //TODO a enlever pour downgrade
		texture = data->texture.door_tex;
	hit = 0;
	if (data->ray.side == 0 || data->ray.side == 1)
		hit = data->ray.pos.y + data->ray.perp_wall_dist * data->ray.ray_dir.y;
	else
		hit = data->ray.pos.x + data->ray.perp_wall_dist * data->ray.ray_dir.x;
	hit -= (int) hit;
	data->ray.tex_x = (int)(hit * (double) texture->width);
	if ((data->ray.side == 0 || data->ray.side == 1) && data->ray.ray_dir.x > 0)
		data->ray.tex_x = texture->width - data->ray.tex_x - 1;
	if ((data->ray.side == 2 || data->ray.side == 3) && data->ray.ray_dir.y < 0)
		data->ray.tex_x = texture->width - data->ray.tex_x - 1;
}

void	drawline(t_data *data, mlx_texture_t *texture, uint32_t **arr, int x)
{
	double	dist;
	double	pos;
	int		tex_y;
	int		j;
	
	if (data->texture.door_flag == 1) //TODO a enlever pour downgrade
	{
		texture = data->texture.door_tex;
		arr = data->texture.door;
		data->texture.door_flag = 0;
	}//jusqu ici
	dist = 1.0 * texture->height / data->ray.line_height;
	pos = ((double) data->ray.draw_start - (double) WINHEIGHT / 2
			+ (double) data->ray.line_height / 2) * dist;
	if (pos < 0)
		pos = 0;
	j = data->ray.draw_start - 1;
	while (++j < data->ray.draw_end)
	{
		tex_y = (int) pos;
		if (pos > texture->height - 1)
			pos = texture->height - 1;
		pos += dist;
		mlx_put_pixel(data->image.window, x, j, arr[tex_y][data->ray.tex_x]);
	}
}

void	choose_texture(t_data *data, int x)
{
	if (data->ray.side == 0)
	{
		find_hit(data, data->texture.east_tex);
		drawline(data, data->texture.east_tex, data->texture.east, x);
	}
	else if (data->ray.side == 1)
	{
		find_hit(data, data->texture.west_tex);
		drawline(data, data->texture.west_tex, data->texture.west, x);
	}
	else if (data->ray.side == 2)
	{
		find_hit(data, data->texture.south_tex);
		drawline(data, data->texture.south_tex, data->texture.south, x);
	}
	else if (data->ray.side == 3)
	{
		find_hit(data, data->texture.north_tex);
		drawline(data, data->texture.north_tex, data->texture.north, x);
	}
}

void	draw_vertline(t_data *data, int x)
{
	int	y;

	y = 0;
	while ((int)y < data->ray.draw_start)
		mlx_put_pixel(data->image.window, x, y++, data->param.ceil);
	while ((int)y < WINHEIGHT)
		mlx_put_pixel(data->image.window, x, y++, data->param.floor);
}

void	track_window(t_data *data)
{
	int32_t	x = 0;
	int32_t	y = 0;
	
	mlx_get_window_pos(data->mlx, &x, &y);
	if(data->param.w_pos_x != x || data->param.w_pos_y != y)
	{
		mlx_set_window_pos(data->mlx, data->param.w_pos_x, data->param.w_pos_y);
	}
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
}

void	loop(void *param)
{
	t_data	*data;
	int		x;

	data = param;
	x = -1;
	while (++x < WINWIDTH)
	{
		set_data(data, x);
		set_side_dist(data);
		dda(data);
		set_draw_range(data);
		draw_vertline(data, x);
		choose_texture(data, x);
		key_binding(data);//TODO a enlever pour downgrade
		mouse_tracking(data);//TODO a enlever pour downgrade
	}
	center_dot(data->image.window);
	mlx_key_hook(data->mlx, &ft_key_detect, data);
	track_window(data);
	draw_minimap(data);
	usleep(1500);
}
