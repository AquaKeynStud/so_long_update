/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_printers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:09:14 by arocca            #+#    #+#             */
/*   Updated: 2025/03/20 11:31:28 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
			ft_printf("[%i, %i] ", i, j++);
		ft_printf("\n");
		j = 0;
		while (j < map->width)
		{
			ft_printf(" %c ", map->map[i][j].type);
			if (map->map[i][j].verified)
				ft_printf("✅  ");
			else
				ft_printf("❌  ");
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

static void	print_type(t_case cell)
{
	if (cell.type != '0' && cell.type != '1')
	{
		if (cell.type == 'C')
			ft_printf("🐱 ");
		else if (cell.type == 'P')
			ft_printf("🎐 ");
		else if (cell.type == 'E')
			ft_printf("🌸 ");
		else if (cell.type == 'M')
			ft_printf("🧫 ");
	}
	else
	{
		if (cell.verified)
			ft_printf("🌱 ");
		else
		{
			if (cell.type == '1')
				ft_printf("🍁 ");
			else
				ft_printf("🍃 ");
		}
	}
}

void	print_verification(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		ft_printf("%4i ", i + 1);
		while (j < map->width)
			print_type(map->map[i][j++]);
		ft_printf("\n");
		i++;
	}
	j = 0;
	ft_printf("%5c", ' ');
	while (j++ < map->width)
	{
		ft_printf("%2i ", j);
	}
	ft_printf("\n");
}

void	print_map_types(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			ft_printf("%c ", map->map[i][j].type);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	print_map_matrices(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			ft_printf("[%i, %i] ", i, j);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
