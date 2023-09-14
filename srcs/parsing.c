
#include "../include/cub3d.h"

int	color_decoder(char *str, uint32_t *surface)
{
	int	i;
	uint32_t temp;
	char *temp_str;
	
	temp_str = NULL;
	temp_str = ft_strtrim(str, " ");
	i = 0;
	*surface = 0;
	while(temp_str[i] && i < 12)
	{
		temp = (uint32_t)ft_atoi(temp_str + i);
		if (temp < 0 || temp > 255)
			return (errhandler(ERRCOLOR));
		*surface = *surface << 8;
		*surface |= temp;
		while (temp_str[i] && temp_str[i] != ',')
			i++;
		if(temp_str[i])
			i++;
	}
	*surface = *surface << 8;
	*surface |= 255;
	free(temp_str);
	return (1);
}

char	*check_path(char *str)
{
	char *wall;
	wall = ft_strtrim(str, " ");
	if (access(wall, F_OK) == -1)
	{
		errhandler(ERRIMG);
		exit(-1);
	}
	return (wall);
}

void	parse_map(t_data *data, int y)
{	
	int x;

	while(data->map[y])
	{
		x = 0;
		while(data->map[y][x])
		{
			if(data->map[y][x] == '1' || data->map[y][x] == '0' || data->map[y][x] == ' ')
				x++;
			else if (data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x] == 'W' || data->map[y][x] == 'E')
			{
				ft_printf("\n%d-%d\n", y, x);
				ft_printf("test");
				if(data->player.map_y == -1)
				{
					data->player.map_x = x;
					data->player.map_y = y;
					ft_printf("\n%d\n", data->player.map_y);
					ft_printf("\n%d\n", data->player.map_x);
					x++;
				}
				else
				{
					errhandler(ERRPLAYER);
					exit(-1);
				}
			}
			else
			{
				errhandler(ERRCHAR);
				exit(-1);
			}
		}
		y++;
	}
	if(data->player.map_x == -1 || data->player.map_x == -1)
	{
		errhandler(ERRNOPLAYER);
		exit(-1);
	}
}

void	parsing(t_data *data)
{
	int	x;
	int	y;
	int start;

	x = 0;
	y = 0;
	start = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			while (data->map[y][x] == ' ' && data->map[y][x])
				x++;
			if (data->map[y][x] == '\0')
				break;
			if (ft_strncmp(&data->map[y][x], "NO ", 3) == 0)
			{	
				data->param.north = check_path(&data->map[y][x + 3]);
			}
			else if (ft_strncmp(&data->map[y][x], "SO ", 3) == 0)
			{	
				data->param.south = check_path(&data->map[y][x + 3]);
			}
			else if (ft_strncmp(&data->map[y][x], "WE ", 3) == 0)
			{	
				data->param.west = check_path(&data->map[y][x + 3]);
			}
			else if (ft_strncmp(&data->map[y][x], "EA ", 3) == 0)
			{	
				data->param.east = check_path(&data->map[y][x + 3]);
			}
			else if (ft_strncmp(&data->map[y][x], "F ", 2) == 0)
			{
				color_decoder(&data->map[y][x + 2], &data->param.floor);
				data->param.flgfloor = 1;
			}
			else if (ft_strncmp(&data->map[y][x], "C ", 2) == 0)
			{
				color_decoder(&data->map[y][x + 2], &data->param.ceil);
				data->param.flgceil = 1;
			}
			else if (data->map[y][x] == '1' && ((!data->param.north) || (!data->param.south) || (!data->param.west) || (!data->param.east) || (data->param.flgceil == 0) || (data->param.flgfloor == 0)))
			{
				errhandler(ERRPARSE);
				exit(-1);
			}
			else if (data->map[y][x] == '1')
			{
				start = y;
				break;
			}
			x++;
		}
		if (data->map[y][x] == '1')
			break;
		y++;
	}
	parse_map(data, start);
}