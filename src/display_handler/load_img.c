/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:43:57 by arocca            #+#    #+#             */
/*   Updated: 2025/03/24 19:05:34 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.h"
#include "utils.h"

bool	free_images(t_data *data, t_images *img)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (img->wall[i])
			mlx_destroy_image(data->mlx, img->wall[i]);
		if (img->player[i])
			mlx_destroy_image(data->mlx, img->player[i]);
		if (img->floor[i])
			mlx_destroy_image(data->mlx, img->floor[i]);
		if (img->slime[i])
			mlx_destroy_image(data->mlx, img->slime[i]);
		if (img->exit[i])
			mlx_destroy_image(data->mlx, img->exit[i]);
		if (img->collec[i])
			mlx_destroy_image(data->mlx, img->collec[i]);
		i++;
	}
	data->images = NULL;
	return (false);
}

static bool	load_images(void *mlx, void **imgs, char **paths)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = SX;
	y = SY;
	while (i < 4)
	{
		imgs[i] = mlx_xpm_file_to_image(mlx, paths[i], &x, &y);
		if (!imgs[i])
		{
			err_v("📛 Error : Failed to load asset : %s", paths[i]);
			while (i--)
			{
				mlx_destroy_image(mlx, imgs[i]);
				imgs[i] = NULL;
			}
			return (false);
		}
		i++;
	}
	return (true);
}

bool	load_anims(t_data *data, t_images *img)
{
	char	*paths[4];

	paths[0] = "./assets/slime1.xpm";
	paths[1] = "./assets/slime2.xpm";
	paths[2] = "./assets/slime3.xpm";
	paths[3] = "./assets/slime4.xpm";
	if (!load_images(data->mlx, img->slime, paths))
		return (false);
	paths[0] = "./assets/collectible1.xpm";
	paths[1] = "./assets/collectible2.xpm";
	paths[2] = "./assets/collectible3.xpm";
	paths[3] = "./assets/collectible4.xpm";
	if (!load_images(data->mlx, img->collec, paths))
		return (false);
	paths[0] = "./assets/exit1.xpm";
	paths[1] = "./assets/exit2.xpm";
	paths[2] = "./assets/exit3.xpm";
	paths[3] = "./assets/exit4.xpm";
	if (!load_images(data->mlx, img->exit, paths))
		return (false);
	return (true);
}

bool	load_textures(t_data *data, t_images *img)
{
	char	*paths[4];

	paths[0] = "./assets/wall1.xpm";
	paths[1] = "./assets/wall2.xpm";
	paths[2] = "./assets/wall3.xpm";
	paths[3] = "./assets/wall4.xpm";
	if (!load_images(data->mlx, img->wall, paths))
		return (false);
	paths[0] = "./assets/p_down.xpm";
	paths[1] = "./assets/p_right.xpm";
	paths[2] = "./assets/p_left.xpm";
	paths[3] = "./assets/p_up.xpm";
	if (!load_images(data->mlx, img->player, paths))
		return (false);
	paths[0] = "./assets/floor1.xpm";
	paths[1] = "./assets/floor2.xpm";
	paths[2] = "./assets/floor3.xpm";
	paths[3] = "./assets/floor4.xpm";
	if (!load_images(data->mlx, img->floor, paths))
		return (false);
	return (true);
}

bool	init_images(t_data *data, t_images *img, int img_nbr)
{
	while (img_nbr)
	{
		img->wall[img_nbr - 1] = NULL;
		img->slime[img_nbr - 1] = NULL;
		img->player[img_nbr - 1] = NULL;
		img->floor[img_nbr - 1] = NULL;
		img->exit[img_nbr - 1] = NULL;
		img->collec[(img_nbr--) - 1] = NULL;
	}
	data->gen = 0;
	img->frame = 0;
	img->direction = 0;
	img->anim_frame = 0;
	data->max_gen = 55000;
	img->anim_speed = 12500;
	if (running_under_valgrind())
	{
		data->max_gen = 6500;
		img->anim_speed = 1500;
	}
	print_info_str("🪷 Loading assets... 🍡", NULL);
	if (!(load_anims(data, img) && load_textures(data, img)))
		return (free_images(data, img));
	print_info_str("🗻 Assets loaded successfully ! 🧬", NULL);
	return (true);
}
