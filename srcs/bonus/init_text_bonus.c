/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouchar <fbouchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:46:44 by emlamoth          #+#    #+#             */
/*   Updated: 2023/10/12 09:11:40 by fbouchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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

void	free_all_texture_array(t_data *data)
{
	if (data->texture.north)
		free_text_ar(data->texture.north_tex, data->texture.north);
	if (data->texture.south)
		free_text_ar(data->texture.south_tex, data->texture.south);
	if (data->texture.east)
		free_text_ar(data->texture.east_tex, data->texture.east);
	if (data->texture.west)
		free_text_ar(data->texture.west_tex, data->texture.west);
	if (data->texture.door)
		free_text_ar(data->texture.door_tex, data->texture.door);
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
	}
	if (!data->texture.north_tex || !data->texture.south_tex 
		|| !data->texture.west_tex || !data->texture.east_tex)
	{
		clean_texture(data);
		cub_exit(data, ERRTEXT);
	}
	data->texture.north = texture_to_array(data->texture.north_tex);
	data->texture.south = texture_to_array(data->texture.south_tex);
	data->texture.east = texture_to_array(data->texture.east_tex);
	data->texture.west = texture_to_array(data->texture.west_tex);
	data->texture.door = texture_to_array(data->texture.door_tex);
	if (!data->texture.north || !data->texture.south 
		|| !data->texture.west || !data->texture.east)
	{
		clean_texture(data);
		cub_exit(data, ERRTEXT);
	}
}

void	clean_texture(t_data *data)
{
	free_all_texture_array(data);
	if (data->texture.door_tex)
		mlx_delete_texture(data->texture.door_tex);
	if (data->texture.north_tex)
		mlx_delete_texture(data->texture.north_tex);
	if (data->texture.south_tex)
		mlx_delete_texture(data->texture.south_tex);
	if (data->texture.east_tex)
		mlx_delete_texture(data->texture.east_tex);
	if (data->texture.west_tex)
		mlx_delete_texture(data->texture.west_tex);
}
