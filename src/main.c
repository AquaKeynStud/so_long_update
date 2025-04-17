/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:45:44 by arocca            #+#    #+#             */
/*   Updated: 2025/03/24 18:35:29 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.h"
#include "bonus.h"

int	close_window(t_data *data, int exit_code)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->map)
		free_map(data->map);
	if (exit_code == EXIT_SUCCESS && data->game_status == VICTORY)
		print_green("🎋 • Congratulation, you won ! • 🏆");
	else if (exit_code == EXIT_SUCCESS && data->game_status == DEFEAT)
		err("🪦  • Player died... D: • ⚰️ ");
	else if (exit_code == EXIT_SUCCESS && data->game_status == RUNNING)
		err("♨️  • So_long program canceled • 🛟");
	exit(exit_code);
}

static bool	window_create(t_data *data, int	*mapw, int *maph)
{
	data->moves = 0;
	data->game_status = RUNNING;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free_map(data->map));
	mlx_get_screen_size(data->mlx, &data->winw, &data->winh);
	data->winw = (data->winw - (data->winw % SX));
	data->winh = (data->winh - (data->winh % SY));
	if (*mapw <= (data->winw / SX))
		data->winw = *mapw * SX;
	if (*maph <= (data->winh / SY))
		data->winh = *maph * SY;
	data->win = mlx_new_window(data->mlx, data->winw, data->winh, "so_long");
	if (!data->win)
	{
		free(data->mlx);
		return (free_map(data->map));
	}
	print_info_int("🖥️  Window size : %ix%i 🪟 ", data->winw, data->winh);
	return (true);
}

int	end_loop(t_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

static bool	verif_ext(char *file, char *ext)
{
	int		len;
	int		pad;

	len = ft_strlen(file);
	pad = ft_strlen(ext);
	if (len < pad || !*file || !*ext)
		return (false);
	while (pad >= 0)
	{
		if (file[len - pad] != ext[ft_strlen(ext) - pad])
			return (false);
		pad--;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_images	images;
	t_map		*map;

	map = NULL;
	data.images = &images;
	print_title();
	if (argc != 2 || !verif_ext(argv[1], ".ber"))
		return (err_v("📛 Error : Format has to be : %s <map>.ber", argv[0]));
	if (!get_map(argv[1], &map, &data))
		return (1);
	if (!window_create(&data, &map->width, &map->height))
		return (err("📛 Error : Something went wrong during window creation"));
	if (!init_images(&data, &images, 4))
		return (close_window(&data, EXIT_FAILURE));
	init_display(data, map, images);
	mlx_hook(data.win, 17, 0, end_loop, &data);
	mlx_hook(data.win, 2, 1L << 0, key_pressed, &data);
	mlx_hook(data.win, 3, 1L << 1, key_released, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	free_images(&data, &images);
	close_window(&data, EXIT_SUCCESS);
}
