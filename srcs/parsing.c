
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

int	check_path(char *str, char *wall)
{
	wall = ft_strtrim(str, " ");
	if (access(wall, F_OK) == -1)
		return (errhandler(ERRIMG));
	return (1);
}

void	parsing(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
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
				if (check_path(&data->map[y][x + 3], data->param.north) == -1)
					exit(-1);
			}
			else if (ft_strncmp(&data->map[y][x], "SO ", 3) == 0)
			{	
				if (check_path(&data->map[y][x + 3], data->param.south) == -1)
					exit(-1);
			}
			else if (ft_strncmp(&data->map[y][x], "WE ", 3) == 0)
			{	
				if (check_path(&data->map[y][x + 3], data->param.west) == -1)
					exit(-1);
			}
			else if (ft_strncmp(&data->map[y][x], "EA ", 3) == 0)
			{	
				if (check_path(&data->map[y][x + 3], data->param.east) == -1)
					exit(-1);
			}
			else if (ft_strncmp(&data->map[y][x], "F ", 2) == 0)
				color_decoder(&data->map[y][x + 2], &data->param.floor);
			else if (ft_strncmp(&data->map[y][x], "C ", 2) == 0)
				color_decoder(&data->map[y][x + 2], &data->param.ceil);
			x++;
		}
		y++;
	}
}