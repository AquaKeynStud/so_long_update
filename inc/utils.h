/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:38:27 by arocca            #+#    #+#             */
/*   Updated: 2025/04/11 15:51:07 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* -- Includes -- */
# include "so_long.h"

/* -- Structure -- */
typedef struct s_maptmp
{
	char			*line;
	struct s_maptmp	*next;
}				t_maptmp;

/* -- Libft functions -- */
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strstr(const char *big, const char *little);

/* -- Utils -- */
char	*ft_itoa(int n);
int		type_of(t_case cell);
int		get_pos(t_map *map, char axis);
bool	err_stuck_by_exit(t_map *dmap);
int		*get_axis(int tab[2], int x, int y);
void	*get_img(t_data *data, t_images img, int y, int x);
int		browse_map(t_map *map, bool (*function)(t_case cell));

/* -- Optimisations -- */
bool	running_under_valgrind(void);
bool	free_list(t_maptmp *head, int fd);
bool	read_err(const char *file, t_maptmp **head, int *height);

#endif