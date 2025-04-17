/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:43:15 by arocca            #+#    #+#             */
/*   Updated: 2025/03/16 12:44:26 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

/* -- Includes -- */
# include "so_long.h"

/* -- Bonus functions -- */
void	animate(t_data *data);
int		game_loop(t_data *data);
int		move_enemies(t_data *data);

#endif