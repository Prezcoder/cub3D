/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:41:30 by fbouchar          #+#    #+#             */
/*   Updated: 2023/10/05 15:17:12 by emlamoth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	flood_fill(int y, int x, t_data *data, char **map_cpy)
{
	if (!map_cpy[y] || x < 0 || x > (int)ft_strlen(map_cpy[y])
		|| y < data->player.start_map || y > data->param.nbline - 1)
	{
		ft_printf("error 1\n");
		exit(-1);
	}
	if (map_cpy[y][x] == '1' || map_cpy[y][x] == 'X')
		return ;
	if (map_cpy[y][x] == 'N' || map_cpy[y][x] == 'S' || map_cpy[y][x] == 'W'
		|| map_cpy[y][x] == 'E' || map_cpy[y][x] == ' ' || map_cpy[y][x] == '2')
		;
	map_cpy[y][x] = 'X';
	flood_fill(y + 1, x, data, map_cpy);
	flood_fill(y - 1, x, data, map_cpy);
	flood_fill(y, x - 1, data, map_cpy);
	flood_fill(y, x + 1, data, map_cpy);
}

void	wall_check(t_data *data)
{
	char	**map_cpy;

	map_cpy = NULL;
	map_cpy = ft_tabdup(data->map);
	flood_fill(data->player.map_y, data->player.map_x, data, map_cpy);
	ft_freeall(map_cpy);
}
