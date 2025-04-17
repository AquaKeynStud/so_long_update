/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_printers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:36:46 by arocca            #+#    #+#             */
/*   Updated: 2025/03/15 11:36:34 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <errno.h>

int	err(char *message)
{
	ft_printf("\033[31m\033[1m\033[107m     ");
	ft_printf(message);
	ft_printf("     \033[0m\n");
	return (ft_strlen(message));
}

int	err_v(char *message, char *value)
{
	ft_printf("\033[31m\033[1m\033[107m     ");
	ft_printf(message, value);
	ft_printf("     \033[0m\n");
	return (ft_strlen(message));
}

int	err_errno(int errnum)
{
	ft_printf("\033[31m\033[1m\033[107m     ");
	ft_printf("Error : %s", strerror(errnum));
	ft_printf("     \033[0m\n");
	return (1);
}
