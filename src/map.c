/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:44:33 by arocca            #+#    #+#             */
/*   Updated: 2025/03/30 18:04:40 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parsing.h"
#include "printers.h"

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
	free((*map)->slime);
	(*map)->slime = NULL;
	free(*map);
	*map = NULL;
	return (false);
}

static int	size_err(t_maptmp *head, int *width)
{
	int			count;
	t_maptmp	*tmp;

	count = 0;
	tmp = head;
	(*width) = 0;
	while (tmp)
	{
		count = ft_strlen(tmp->line);
		count -= (tmp->line[ft_strlen(tmp->line) - 1] == '\n');
		if (!count || count > 28000 || (count != (*width) && (*width) != 0))
		{
			free_list(head, 0);
			return (err("The map size is invalid"));
		}
		(*width) = count;
		count = 0;
		tmp = tmp->next;
	}
	return (0);
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
			map->map[i][j].rand_asset = rand() % 4;
			map->map[i][j].verified = false;
			j++;
		}
		i++;
	}
	map->map[i] = NULL;
	return (true);
}

static void	fill_map(t_maptmp *head, t_map *map)
{
	int			i;
	int			j;
	t_maptmp	*tmp;

	i = 0;
	tmp = head;
	map->items = 0;
	while (tmp)
	{
		j = 0;
		while (j < map->width)
		{
			map->map[i][j].type = tmp->line[j];
			if (tmp->line[j] == 'C')
				map->items++;
			j++;
		}
		tmp = tmp->next;
		i++;
	}
}

bool	get_map(const char *file, t_map **map, t_data *data)
{
	t_maptmp	*tmp;

	tmp = NULL;
	(*map) = ft_calloc(sizeof(t_map), 1);
	if (!(*map))
		return (false);
	print_info_str("🧭 Start reading attempt on 🗺️  %s 🗺️ ", (char *)file);
	if (read_err(file, &tmp, &(*map)->height) || size_err(tmp, &(*map)->width))
		return (free_map(map));
	if ((*map)->height > 27000)
	{
		err("📛 Error : Map height is too big");
		return (free_map(map));
	}
	print_info_str("🌅 Starting creation of map... 🧪", NULL);
	init_map(*map);
	print_info_str("🍲 Start filling the map... 🀄", NULL);
	fill_map(tmp, (*map));
	free_list(tmp, 0);
	get_axis(data->pyx, get_pos(*map, 'y'), get_pos(*map, 'x'));
	if (err_map_parsing(*map, data, file) || !get_slimes(*map))
		return (free_map(map));
	data->map = map;
	print_info_int("🏔️  Map size : %ix%i 🏞️ ", (*map)->width, (*map)->height);
	return (true);
}
