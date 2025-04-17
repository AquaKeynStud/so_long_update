/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_on_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 10:26:45 by arocca            #+#    #+#             */
/*   Updated: 2025/03/20 17:05:19 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printers.h"

static int	count_digit(int n)
{
	int	count;

	count = 1;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static long	make_lpos(int n)
{
	long	nbr;

	nbr = (long)n;
	if (nbr < 0)
		return (nbr *= -1);
	else
		return (nbr);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		digit_nbr;
	long	pos_nbr;

	pos_nbr = make_lpos(n);
	digit_nbr = count_digit(n) - (n > 0);
	str = (char *)malloc(digit_nbr + 1);
	if (!str)
		return (NULL);
	str[digit_nbr] = '\0';
	while (digit_nbr--)
	{
		str[digit_nbr] = '0' + pos_nbr % 10;
		pos_nbr /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

void	print_on_win(t_data *data, int *axis, int color, char *txt)
{
	mlx_string_put(data->mlx, data->win, axis[0] + 1, axis[1] + 1, BLACK, txt);
	mlx_string_put(data->mlx, data->win, axis[0] + 1, axis[1] - 1, BLACK, txt);
	mlx_string_put(data->mlx, data->win, axis[0] - 1, axis[1] + 1, BLACK, txt);
	mlx_string_put(data->mlx, data->win, axis[0] - 1, axis[1] - 1, BLACK, txt);
	mlx_string_put(data->mlx, data->win, axis[0], axis[1] - 1, BLACK, txt);
	mlx_string_put(data->mlx, data->win, axis[0], axis[1] + 1, BLACK, txt);
	mlx_string_put(data->mlx, data->win, axis[0] - 1, axis[1], BLACK, txt);
	mlx_string_put(data->mlx, data->win, axis[0] + 1, axis[1], BLACK, txt);
	mlx_string_put(data->mlx, data->win, axis[0], axis[1], color, txt);
}

void	print_win(t_data *data, int pos[2], char *text, int moves)
{
	char	*str;
	t_map	*map;
	int		letter_width;
	int		x_len;
	int		y_len;

	letter_width = 6;
	x_len = pos[0] / SX;
	y_len = pos[1] / SY;
	map = (*data->map);
	if (map->height < (data->winh / SY) || map->width < (data->winw / SX))
		update_images(data, &map->map[y_len][x_len + 1], x_len, y_len);
	if (*text)
	{
		print_on_win(data, pos, WHITE, text);
		pos[0] += (ft_strlen(text) * letter_width) + 5;
	}
	if (moves != -1)
	{
		str = ft_itoa(moves);
		print_on_win(data, pos, WHITE, str);
		free(str);
	}
}
