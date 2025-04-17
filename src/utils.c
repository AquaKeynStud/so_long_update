/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:51:56 by arocca            #+#    #+#             */
/*   Updated: 2025/03/14 15:12:55 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	browse_map(t_map *map, bool (*function)(t_case cell))
{
	int	i;
	int	j;
	int	counter;

	i = 0;
	counter = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (function(map->map[i][j]))
				counter++;
			j++;
		}
		i++;
	}
	return (counter);
}

int	get_pos(t_map *map, char axis)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j].type == 'P' && axis == 'x')
				return (map->map[i][j].x);
			else if (map->map[i][j].type == 'P' && axis == 'y')
				return (map->map[i][j].y);
			j++;
		}
		i++;
	}
	return (0);
}

int	type_of(t_case cell)
{
	char	*types;
	int		i;

	types = "01PCEM";
	i = 0;
	while (types[i])
	{
		if (types[i] == cell.type)
			return (i);
		i++;
	}
	return (-1);
}

void	*get_img(t_data *data, t_images img, int y, int x)
{
	int		type;
	t_map	*map;

	map = (*data->map);
	type = type_of(map->map[y][x]);
	if (type == 0)
		return (img.floor[map->map[y][x].rand_asset]);
	if (type == 1)
		return (img.wall[map->map[y][x].rand_asset]);
	if (type == 2)
		return (img.player[img.direction]);
	if (type == 3)
		return (img.collec[img.frame]);
	if (type == 4)
		return (img.exit[img.frame]);
	if (type == 5)
		return (img.slime[img.frame]);
	return (NULL);
}

int	*get_axis(int tab[2], int x, int y)
{
	tab[0] = x;
	tab[1] = y;
	return (tab);
}
