/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:50:10 by arocca            #+#    #+#             */
/*   Updated: 2025/03/16 12:45:03 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "utils.h"

void	animate(t_data *data)
{
	t_map		*map;
	t_images	*image;
	int			pos[2];

	map = *data->map;
	image = data->images;
	if (++image->anim_frame < image->anim_speed)
		return ;
	image->anim_frame = 0;
	image->frame = (image->frame + 1) % 4;
	get_axis(pos, data->pyx[1], data->pyx[0]);
	init_display(*data, map, *image);
}

int	game_loop(t_data *data)
{
	animate(data);
	move_enemies(data);
	return (0);
}
