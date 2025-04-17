/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:30:30 by arocca            #+#    #+#             */
/*   Updated: 2025/03/24 19:12:09 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.h"
#include "utils.h"

void	update_display(t_data *data, t_map *map, t_case *aim)
{
	int		pos[2];
	int		winw;
	int		winh;
	int		padding;

	winw = data->winw;
	winh = data->winh;
	padding = ((ft_strlen("Player x:") + 6) * CHARW) / 2;
	if (map->height > (data->winh / SY) || map->width > (data->winw / SX))
		display_player(data, get_axis(pos, aim->x, aim->y), *data->images, map);
	else
		update_images(data, aim, data->pyx[1], data->pyx[0]);
	print_win(data, get_axis(pos, 10, winh - 5), "Moves :", ++data->moves);
	print_win(data, get_axis(pos, winw / 2 - padding, 20), "Player x:", aim->x);
	print_win(data, get_axis(pos, winw / 2 + padding, 20), "y:", aim->y);
	print_win(data, get_axis(pos, 10, 20), "Collectibles :", map->items);
	ft_printf("\033[35m\033[1m\033[107m      ");
	ft_printf("𝗠𝗼𝘃𝗲𝘀 ➤ %i", data->moves);
	ft_printf("     \033[0m\n");
}

bool	move_player(t_data *data, t_map *map, t_case *aim)
{
	int		x;
	int		y;

	y = data->pyx[0];
	x = data->pyx[1];
	if (aim->type == '1')
		return (true);
	else if (aim->type == 'E' && map->items != 0)
		return (err("🏮 You must have collected all the cats before exiting !"));
	if (aim->type == 'C')
	{
		map->items--;
		map->map[y][x].rand_asset = 0;
	}
	else if (aim->type == 'E' || aim->type == 'M')
	{
		data->game_status = VICTORY * aim->type == 'E';
		return (mlx_loop_end(data->mlx));
	}
	map->map[y][x].type = '0';
	aim->type = 'P';
	update_display(data, map, aim);
	data->pyx[0] = aim->y;
	data->pyx[1] = aim->x;
	return (true);
}
