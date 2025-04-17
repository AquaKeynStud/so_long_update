/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:01:35 by arocca            #+#    #+#             */
/*   Updated: 2025/04/11 15:55:01 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include "printers.h"

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
		str[i++] = c;
	return (s);
}

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i])
	{
		j = 0;
		while (little[j] && big[i + j] == little[j])
			j++;
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size || size > SIZE_MAX / nmemb)
		return (NULL);
	tab = malloc(size * nmemb);
	if (!tab)
		return (NULL);
	ft_memset(tab, 0, size * nmemb);
	return (tab);
}

static bool	is_wall(t_case cell)
{
	return (cell.type == 'E' || !cell.verified);
}

bool	err_stuck_by_exit(t_map *dmap)
{
	int		i;
	int		j;
	t_case	**map;

	i = 0;
	map = dmap -> map;
	while (i < dmap->height)
	{
		j = 0;
		while (j < dmap->width)
		{
			if (map[i][j].type == 'C' || map[i][j].type == 'P')
			{
				if (is_wall(map[i + 1][j]) && is_wall(map[i - 1][j])
					&& is_wall(map[i][j + 1]) && is_wall(map[i][j - 1]))
					return (err("📛 Error : Something is stuck by the exit"));
			}
			j++;
		}
		i++;
	}
	return (false);
}
