/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:31:01 by arocca            #+#    #+#             */
/*   Updated: 2025/01/15 14:31:01 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
int		parse_args(char *s, va_list *args, size_t *total_len);

int		mandatory_parser(char c, va_list *args, size_t *total_len, int err);
void	format_update(char **s, size_t	*i, size_t *len, va_list *args);
char	check_conv(char c);

int		handle_string(va_list *args, size_t *total_len, int err);
int		handle_char(va_list *args, size_t *total_len, int err);
int		handle_nbr(va_list *args, size_t *total_len, int isInt, int err);
int		handle_address(va_list *args, size_t *total_len, int err);
int		handle_hexa(va_list *args, size_t *total_len, int isLower, int err);

void	ft_putnbr_fd(int n, int fd, size_t *total_len, int (*f)[8]);
void	ft_putunbr_fd(unsigned int n, int fd, size_t *total_len, int (*f)[8]);
void	ft_print_memory(void *addr, size_t *total_len);
void	convert_to(unsigned long a, char *base, size_t *total_len);

int		c_d(int nb);
int		fill(char c, int len, int (*f)[8], int both);
int		authorized_c(char c);
int		addr_len(void *addr);
int		x_len(unsigned int nb);

size_t	ft_strlen(const char *str);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);

void	create_nbr(char c, va_list *args, size_t *total_len, int (*f)[8]);
void	create_x(char c, va_list *args, size_t *total_len, int (*f)[8]);
void	create_addr(va_list *args, size_t *total_len, int (*f)[8]);
void	create_string(va_list *args, size_t *total_len, int (*f)[8]);

void	print_nb_bonus(int nbr, size_t *total_len, int (*f)[8]);
void	print_char_bonus(int n, size_t *total_len, int (*f)[8]);
void	print_addr_bonus(void *arg, size_t *total_len, int (*f)[8]);
void	print_uint_bonus(unsigned int arg, size_t *total_len, int (*f)[8]);
void	print_x_bonus(unsigned int n, size_t *total_len, int (*f)[8], char **b);
void	print_x_left(unsigned int n, size_t *total_len, int (*f)[8], char **b);
void	print_str_bonus(char *str, size_t *total_len, int (*f)[8]);
void	ft_print_memory_bonus(void *addr, size_t *total_len, int (*f)[8]);
void	write_sign(int *n, size_t *total_len, int (*f)[8]);

int		handle_tab_two_char_err(char *s, size_t len, size_t *total_len);
int		handle_char_err(char *s, size_t len, size_t *total_len, va_list *args);
int		error_parser(char *s, size_t len, size_t *total_len);
int		error_tab(char *s);

#endif