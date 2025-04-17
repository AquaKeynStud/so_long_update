/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_so_long.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:51:04 by arocca            #+#    #+#             */
/*   Updated: 2025/04/11 15:51:40 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDATORY_SO_LONG_H
# define MANDATORY_SO_LONG_H

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
	void	*wall;
	void	*exit;
	void	*floor;
	void	*collec;
	void	*player;
}				t_images;

typedef struct s_case
{
	int		x;
	int		y;
	char	type;
	bool	verified;
}				t_case;

typedef struct s_map
{
	int		items;
	int		width;
	int		height;
	t_case	**map;
}				t_map;

typedef struct s_data
{
	int			winw;
	int			winh;
	int			moves;
	int			pyx[2];
	void		*mlx;
	void		*win;
	t_images	*images;
	t_map		**map;
}				t_data;

typedef struct s_queue
{
	t_case	**q;
	int		front;
	int		rear;
	int		size;
}				t_queue;

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

/* -- MinilibX functions -- */
int		end_loop(t_data *data);
int		close_window(t_data *data, int exit_code);

/* -- Map functions -- */
bool	free_map(t_map **map);
bool	get_map(const char *file, t_map **map_data, t_data *data);

/* -- Parsing functions -- */
bool	is_item_unreachable(t_case cell);
bool	err_stuck_by_exit(t_map *dmap);
bool	bfs(t_map *map, int start_x, int start_y);
int		err_map_parsing(t_map *map, t_data *data);

/* -- Input functions -- */
int		handle_keypress(int keycode, t_data *data);

/* -- Display functions -- */
bool	init_images(t_data *data, t_images *img);
bool	free_images(t_data *data, t_images *img);
void	update_images(t_data *data, t_case *aim, int x, int y);
void	display_images(t_data *data, t_images img, t_map *map_data);

/* -- Print functions -- */
int		err(void);
void	print_title(void);
void	print_verification(t_map *map);

/* -- Utils functions -- */
bool	is_wall(t_case cell);
int		type_of(t_case cell);
int		get_pos(t_map *map, char axis);
int		*get_axis(int tab[2], int x, int y);
void	*ft_calloc(size_t nmemb, size_t size);
void	*get_img(t_data *data, t_images img, int y, int x);
int		browse_map(t_map *map, bool (*function)(t_case cell));

#endif