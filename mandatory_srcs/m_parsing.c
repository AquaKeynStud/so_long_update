/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:55:15 by arocca            #+#    #+#             */
/*   Updated: 2025/04/11 15:51:44 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_so_long.h"

static bool	isnt_wall_surrounded(t_map *map, int width, int height)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (map->map[i][0].type != '1' || map->map[i][width].type != '1')
			return (ft_printf("Error\n"));
		i++;
	}
	i = 0;
	while (i < map->width)
	{
		if (map->map[0][i].type != '1' || map->map[height][i].type != '1')
			return (ft_printf("Error\n"));
		i++;
	}
	return (false);
}

static bool	err_tp(t_case cell)
{
	return (type_of(cell) < 0);
}

static bool	err_p(t_case cell)
{
	return (cell.type == 'P');
}

static bool	err_e(t_case cell)
{
	return (cell.type == 'E');
}

int	err_map_parsing(t_map *map, t_data *data)
{
	if ((map->width <= 2 && map->height <= 2))
		return (ft_printf("Error while parsing\n"));
	if (isnt_wall_surrounded(map, map->width - 1, map->height - 1))
		return (1);
	if (browse_map(map, err_tp) || browse_map(map, err_p) != 1
		|| browse_map(map, err_e) != 1 || map->items == 0)
		return (ft_printf("Error while parsing\n"));
	if (bfs(map, data->pyx[1], data->pyx[0]))
		return (ft_printf("Error while parsing\n"));
	if (browse_map(map, is_item_unreachable))
		return (ft_printf("Error while parsing\n"));
	return (0);
}
