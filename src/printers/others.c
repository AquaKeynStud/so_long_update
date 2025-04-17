/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:32:03 by arocca            #+#    #+#             */
/*   Updated: 2025/03/17 13:13:28 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	print_info_int(char *message, int v, int k)
{
	ft_printf("\033[34m\033[1m\033[107m%5cℹ️  Info : ", ' ');
	ft_printf(message, v, k);
	ft_printf("%5c\033[0m\n", ' ');
	return (ft_strlen(message));
}

int	print_info_str(char *message, char *value)
{
	ft_printf("\033[34m\033[1m\033[107m%5cℹ️  Info : ", ' ');
	ft_printf(message, value);
	ft_printf("%5c\033[0m\n", ' ');
	return (ft_strlen(message));
}

int	print_green(char *message)
{
	ft_printf("\033[32m\033[1m\033[107m%5c", ' ');
	ft_printf(message);
	ft_printf("%5c\033[0m\n", ' ');
	return (ft_strlen(message));
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
