/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:51:04 by arocca            #+#    #+#             */
/*   Updated: 2025/03/27 16:00:25 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* -- Includes -- */
# include "mlx.h"
# include "mlx_int.h"
# include <stdlib.h>
# include <stdbool.h>
# include "ft_printf.h"
# include "get_next_line.h"

/* -- Structures -- */
typedef struct s_images
{
	int		frame;
	int		direction;
	int		anim_frame;
	int		anim_speed;
	void	*wall[4];
	void	*exit[4];
	void	*floor[4];
	void	*collec[4];
	void	*player[4];
	void	*slime[4];
}				t_images;

typedef struct s_case
{
	int		x;
	int		y;
	int		rand_asset;
	char	type;
	bool	verified;
}				t_case;

typedef struct s_map
{
	int		items;
	int		width;
	int		height;
	int		slimes;
	t_case	**map;
	t_case	**slime;
}				t_map;

typedef struct s_data
{
	int			gen;
	int			winw;
	int			winh;
	int			moves;
	int			pyx[2];
	int			max_gen;
	int			game_status;
	void		*mlx;
	void		*win;
	bool		keys[256];
	t_images	*images;
	t_map		**map;
}				t_data;

/* -- macros -- */
# define SX 64
# define SY 64

# define CHARW 6

# define KEY_W 122 // 119
# define KEY_A 113 // 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_ESC 65307

# define DEFEAT 0
# define VICTORY 1
# define RUNNING 2

/* -- Game functions -- */
int		end_loop(t_data *data);
int		close_window(t_data *data, int exit_code);

/* -- Map functions -- */
bool	free_map(t_map **map);
bool	get_map(const char *file, t_map **map_data, t_data *data);

/* -- Input functions -- */
int		key_pressed(int keycode, t_data *data);
int		key_released(int keycode, t_data *data);
int		handle_keypress(int keycode, t_data *data);
bool	move_player(t_data *data, t_map *map, t_case *aim);

/* -- Display functions -- */
bool	free_images(t_data *data, t_images *img);
bool	init_images(t_data *data, t_images *img, int img_nbr);

void	update_display(t_data *data, t_map *map, t_case *aim);
void	update_images(t_data *data, t_case *aim, int x, int y);
void	init_display(t_data data, t_map *map, t_images images);
void	display_images(t_data *data, t_images img, t_map *map_data);
void	display_player(t_data *data, int *pos, t_images img, t_map *map_data);

#endif