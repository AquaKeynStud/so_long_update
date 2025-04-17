/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:44:33 by arocca            #+#    #+#             */
/*   Updated: 2025/04/11 14:56:07 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_so_long.h"

bool	free_map(t_map **map)
{
	t_case	**tmp;

	if (!map || !(*map))
		return (false);
	if ((*map)->map)
	{
		tmp = (*map)->map;
		while (*tmp)
			free(*tmp++);
		free((*map)->map);
		(*map)->map = NULL;
	}
	free(*map);
	*map = NULL;
	return (false);
}

static int	map_size_init_err(const char *file, int *width, int *height)
{
	int		fd;
	int		count;
	char	c;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error while attempting to read the map\n"));
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			if (!count || ((*width) && count != (*width)) || (*width > 31))
				return (close(fd) + ft_printf("Error : map size invalid\n"));
			(*width) = count;
			(*height)++;
			count = 0;
		}
		else
			count++;
	}
	if (count && count == (*width))
		(*height)++;
	return (close(fd));
}

static bool	init_map(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	map->map = malloc(sizeof(t_case *) * (map->height + 1));
	if (!map->map)
		return (false);
	while (i < map->height)
	{
		map->map[i] = malloc(sizeof(t_case) * map->width);
		if (!map->map[i])
			return (free_map(&map));
		j = 0;
		while (j < map->width)
		{
			map->map[i][j].x = j;
			map->map[i][j].y = i;
			map->map[i][j].verified = false;
			j++;
		}
		i++;
	}
	map->map[i] = NULL;
	return (true);
}

static void	fill_map(const char *file, t_map *map)
{
	char	c;
	int		i;
	int		j;
	int		fd;

	i = 0;
	map->items = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			read(fd, &c, 1);
			map->map[i][j].type = c;
			if (c == 'C')
				map->items++;
			j++;
		}
		read(fd, &c, 1);
		i++;
	}
	close(fd);
}

bool	get_map(const char *file, t_map **map, t_data *data)
{
	(*map) = ft_calloc(sizeof(t_map), 1);
	if (!(*map))
		return (false);
	(*map)->width = 0;
	(*map)->height = 0;
	if (map_size_init_err(file, &(*map)->width, &(*map)->height))
		return (free_map(map));
	if ((*map)->height >= 17)
	{
		ft_printf("Error : map size invalid\n");
		return (free_map(map));
	}
	init_map(*map);
	fill_map(file, (*map));
	get_axis(data->pyx, get_pos(*map, 'y'), get_pos(*map, 'x'));
	if (err_map_parsing(*map, data))
		return (free_map(map));
	data->map = map;
	return (true);
}
