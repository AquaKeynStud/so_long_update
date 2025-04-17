/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:15:19 by arocca            #+#    #+#             */
/*   Updated: 2025/03/21 13:04:39 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_so_long.h"

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
