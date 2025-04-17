/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_bfs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:44:59 by arocca            #+#    #+#             */
/*   Updated: 2025/04/11 15:56:58 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_so_long.h"

t_queue	*queue_init(t_map *map, int start_x, int start_y)
{
	t_queue	*q;

	q = malloc(sizeof(t_queue));
	if (!q)
		return (NULL);
	q->q = malloc(sizeof(t_case *) * (map->width * map->height));
	if (!q->q)
		return (free(q), NULL);
	q->front = 0;
	q->rear = 0;
	q->size = map->width * map->height;
	q->q[q->rear++] = &map->map[start_y][start_x];
	map->map[start_y][start_x].verified = true;
	return (q);
}

static bool	handle_direction(t_map *map, t_queue *q, t_case *c, int direction)
{
	int	x;
	int	y;

	x = c->x;
	y = c->y;
	if (direction == 0)
		x--;
	else if (direction == 1)
		y++;
	else if (direction == 2)
		x++;
	else
		y--;
	if (x < 0 || y < 0 || y >= map -> height || x >= map -> width)
		return (false);
	if (!map->map[y][x].verified && map->map[y][x].type != '1')
	{
		if (map->map[y][x].type == 'E')
			return (true);
		map->map[y][x].verified = true;
		if (q->rear < q->size)
			q->q[q->rear++] = &map->map[y][x];
	}
	return (false);
}

bool	bfs(t_map *map, int start_x, int start_y)
{
	int		i;
	t_case	*cell;
	t_queue	*queue;
	bool	no_exit;

	no_exit = true;
	queue = queue_init(map, start_x, start_y);
	if (!queue)
		return (true);
	while (queue->front != queue->rear)
	{
		i = 0;
		cell = queue->q[queue->front++];
		while (i < 4)
		{
			if (handle_direction(map, queue, cell, i))
				no_exit = false;
			i++;
		}
	}
	free(queue->q);
	free(queue);
	return (no_exit);
}

bool	is_item_unreachable(t_case cell)
{
	if (cell.verified == true || cell.type == '1'
		|| cell.type == '0' || cell.type == 'E')
		return (false);
	return (true);
}
