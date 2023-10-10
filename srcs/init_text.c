/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:46:44 by emlamoth          #+#    #+#             */
/*   Updated: 2023/10/10 11:20:22 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_text_ar(mlx_texture_t *texture, uint32_t **ar)
{
	uint32_t	y;

	y = 0;
	while (y < texture->height)
	{
		free(ar[y]);
		ar[y] = NULL;
		y++;
	}
	free(ar);
	ar = NULL;
}

void	fill_array(mlx_texture_t *texture, uint32_t **ar)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	i;

	i = 0;
	y = 0;
	while (y < texture->height - 1)
	{
		x = 0;
		while (x < texture->width)
		{
			ar[y][x] = ft_color((uint32_t)texture->pixels[i],
					(uint32_t)texture->pixels[i + 1],
					(uint32_t)texture->pixels[i + 2],
					(uint32_t)texture->pixels[i + 3]);
			i += 4;
			x++;
		}
		y++;
	}
}

uint32_t	**texture_to_array(mlx_texture_t *texture)
{
	uint32_t	y;
	uint32_t	**ar;

	y = 0;
	ar = ft_calloc(texture->height + 1, sizeof(uint32_t *));
	if (!ar)
		return (NULL);
	while (y < texture->height)
	{
		ar[y] = ft_calloc(texture->width, sizeof(uint32_t));
		if (!ar[y])
		{
			free_text_ar(texture, ar);
			return (NULL);
		}
		y++;
	}
	fill_array(texture, ar);
	return (ar);
}

//TODO free les array de texture
void	free_all_array(t_data *data)
{
	if (data->texture.north)
		free_text_ar(data->texture.north_tex, data->texture.north);
	if (data->texture.south)
		free_text_ar(data->texture.south_tex, data->texture.south);
	if (data->texture.east)
		free_text_ar(data->texture.east_tex, data->texture.east);
	if (data->texture.west)
		free_text_ar(data->texture.west_tex, data->texture.west);
}

void	init_texture(t_data *data)
{
	if (data->param.door)
	{
		data->texture.door_tex = mlx_load_png(data->param.door);
		data->texture.north_tex = mlx_load_png(data->param.north);
		data->texture.south_tex = mlx_load_png(data->param.south);
		data->texture.east_tex = mlx_load_png(data->param.east);
		data->texture.west_tex = mlx_load_png(data->param.west);
		data->texture.door_tex = mlx_load_png(data->param.door);
	}
	if (!data->texture.north_tex || !data->texture.south_tex 
		|| !data->texture.west_tex || !data->texture.east_tex)
	{
		errhandler("PNG loading fail");
		exit(-1); //TODO fonction pour free
	}
	data->texture.north = texture_to_array(data->texture.north_tex);
	data->texture.south = texture_to_array(data->texture.south_tex);
	data->texture.east = texture_to_array(data->texture.east_tex);
	data->texture.west = texture_to_array(data->texture.west_tex);
	if (data->param.door)
		data->texture.door = texture_to_array(data->texture.door_tex);
	if (!data->texture.north || !data->texture.south 
		|| !data->texture.west || !data->texture.east)
	{
		errhandler("PNG loading fail");
		exit(-1); //TODO fonction pour free
	}
}
