/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:09:14 by arocca            #+#    #+#             */
/*   Updated: 2025/03/21 14:17:04 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory_so_long.h"

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
	ft_printf("blblblb i : %i\n", map->height);
	while (i < map->height)
	{
		ft_printf("Voici le i : %i\n", i);
		j = 0;
		ft_printf("%4i ", i + 1);
		while (j < map->width)
		{
			print_type(map->map[i][j]);
			j++;
			ft_printf("Voici le j : %i\n", j);
		}
		ft_printf("\n");
		i++;
	}
	j = 0;
	ft_printf("%5c", ' ');
	while (j++ < map->width)
		ft_printf("%2i ", j);
	ft_printf("\n");
}

void	print_title(void)
{
	ft_printf("\n\033[32m\033[107m\033[1m");
	ft_printf("╭━━━━━━━━━════════╕ ❖ SO_LONG ❖ ╒════════━━━━━━━━━╮");
	ft_printf("\033[0m\n\033[32m\033[107m\033[1m");
	ft_printf("│%5c⛲ • Welcome to so_long by Keyn 🫧 • 🎍%5c│", ' ', ' ');
	ft_printf("\033[0m\n\033[32m\033[107m\033[1m");
	ft_printf("╰━━━━━━━━━══════╛ 🍂 さよ•なら 🪼 ╘══════━━━━━━━━━╯");
	ft_printf("\033[0m\n\n");
}
