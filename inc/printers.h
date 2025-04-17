/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:33:19 by arocca            #+#    #+#             */
/*   Updated: 2025/03/20 17:00:00 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTERS_H
# define PRINTERS_H

/* -- Includes -- */
# include "so_long.h"

/* -- Macros -- */
# define BLACK 0x000000
# define WHITE 0xFFFFFF

/* -- Functions -- */
int		err(char *message);
int		err_errno(int errnum);
int		err_v(char *message, char *value);

void	print_title(void);
int		print_green(char *message);
int		print_info_int(char *message, int i, int j);
int		print_info_str(char *message, char *i);

void	print_map(t_map *map);
void	print_verification(t_map *map);
void	print_win(t_data *data, int pos[2], char *text, int moves);
void	print_on_win(t_data *data, int *axis, int color, char *txt);

#endif