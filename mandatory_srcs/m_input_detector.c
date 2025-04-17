/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_input_detector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:40:53 by arocca            #+#    #+#             */
/*   Updated: 2025/03/24 18:08:11 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_so_long.h"

static bool	move_player(t_data *data, t_map *map, t_case *aim)
{
	int		x;
	int		y;

	y = data->pyx[0];
	x = data->pyx[1];
	if (aim->type == '1')
		return (true);
	else if (aim->type == 'E' && map->items != 0)
		return (true);
	if (aim->type == 'C')
		map->items--;
	else if (aim->type == 'E')
		return (mlx_loop_end(data->mlx));
	map->map[y][x].type = '0';
	aim->type = 'P';
	update_images(data, aim, x, y);
	data->pyx[0] = aim->y;
	data->pyx[1] = aim->x;
	data->moves++;
	ft_printf("Moves : %i\n", data->moves);
	return (true);
}

static int	check_input(int keycode)
{
	int	input[10];
	int	i;

	i = 0;
	input[0] = KEY_ESC;
	input[1] = KEY_S;
	input[2] = KEY_D;
	input[3] = KEY_A;
	input[4] = KEY_W;
	input[5] = KEY_DOWN;
	input[6] = KEY_RIGHT;
	input[7] = KEY_LEFT;
	input[8] = KEY_UP;
	input[9] = 0;
	while (i < 9)
	{
		if (keycode == input[i])
			return (i);
		i++;
	}
	return (-1);
}

int	handle_keypress(int keycode, t_data *data)
{
	t_case		**map;
	t_case		*aim;

	map = (*data->map)->map;
	if (check_input(keycode) < 0)
		return (ft_printf("🫧 Cette touche n'est pas attribuée 🫧\n"));
	if (keycode == KEY_ESC)
		return (mlx_loop_end(data->mlx));
	if (keycode == KEY_W || keycode == KEY_UP)
		aim = &map[data->pyx[0] - 1][data->pyx[1]];
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		aim = &map[data->pyx[0]][data->pyx[1] - 1];
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		aim = &map[data->pyx[0] + 1][data->pyx[1]];
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		aim = &map[data->pyx[0]][data->pyx[1] + 1];
	else
		return (0);
	move_player(data, *data->map, aim);
	return (0);
}
