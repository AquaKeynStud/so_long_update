/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:15:19 by arocca            #+#    #+#             */
/*   Updated: 2025/03/20 17:06:38 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.h"
#include "utils.h"

static void	init_bounds(t_data *data, t_map *map, int *pos, int *bound)
{
	bound[0] = pos[0] - ((data->winw / SX) / 2);
	bound[1] = pos[0] + ((data->winw / SX) / 2);
	bound[2] = pos[1] - ((data->winh / SY) / 2);
	bound[3] = pos[1] + ((data->winh / SY) / 2);
	if (bound[2] < 0)
	{
		bound[3] += -bound[2];
		bound[2] = 0;
	}
	if (bound[3] > map->height)
	{
		bound[2] -= bound[3] - map->height;
		bound[3] = map->height;
	}
	if (bound[0] < 1)
	{
		bound[1] += -bound[0];
		bound[0] = 0;
	}
	if (bound[1] > map->width - 1)
	{
		bound[0] -= bound[1] - map->width;
		bound[1] = map->width;
	}
}

void	display_images(t_data *data, t_images img, t_map *map)
{
	int		x;
	int		y;
	void	*mlx;
	void	*win;
	void	*image;

	y = 0;
	mlx = data->mlx;
	win = data->win;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			image = get_img(data, img, y, x);
			if (image)
				mlx_put_image_to_window(mlx, win, image, x * SX, y * SY);
			x++;
		}
		y++;
	}
}

void	display_player(t_data *data, int *pos, t_images imgs, t_map *map)
{
	int		x;
	int		y;
	int		bounds[4];
	int		reset_x;
	void	*img;

	y = 0;
	init_bounds(data, map, pos, bounds);
	reset_x = bounds[0];
	while (bounds[2] < bounds[3])
	{
		x = 0;
		bounds[0] = reset_x;
		while (bounds[0] < bounds[1])
		{
			img = get_img(data, imgs, bounds[2], bounds[0]);
			if (!img)
				return ;
			mlx_put_image_to_window(data->mlx, data->win, img, x * SX, y * SY);
			bounds[0]++;
			x++;
		}
		bounds[2]++;
		y++;
	}
}

void	update_images(t_data *data, t_case *aim, int x, int y)
{
	void		*mlx;
	void		*win;
	void		*img1;
	void		*img2;
	t_images	*img;

	mlx = data->mlx;
	win = data->win;
	img = data->images;
	img1 = get_img(data, *img, y, x);
	img2 = get_img(data, *img, aim->y, aim->x);
	mlx_put_image_to_window(mlx, win, img1, x * SX, y * SY);
	mlx_put_image_to_window(mlx, win, img2, aim->x * SX, aim->y * SY);
}

void	init_display(t_data data, t_map *map, t_images images)
{
	int	winw;
	int	winh;
	int	pos[2];
	int	*pyx;
	int	pad;

	pyx = data.pyx;
	winw = data.winw;
	winh = data.winh;
	pad = ((ft_strlen("Player x:") + 6) * CHARW) / 2;
	get_axis(pos, data.pyx[1], data.pyx[0]);
	if (map->height > (data.winh / SY) || map->width > (data.winw / SX))
		display_player(&data, pos, images, map);
	else
		display_images(&data, images, map);
	print_win(&data, get_axis(pos, 10, winh - 5), "Moves :", data.moves);
	print_win(&data, get_axis(pos, winw / 2 - pad, 20), "Player x:", pyx[1]);
	print_win(&data, get_axis(pos, winw / 2 + pad, 20), "y:", pyx[0]);
	print_win(&data, get_axis(pos, 10, 20), "Collectibles :", map->items);
}
