/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:43:39 by jolivier          #+#    #+#             */
/*   Updated: 2022/10/19 18:08:23 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);

int		ft_putchar(char c);
int		ft_putstr(char *str);

int		ft_putnbr_count(int n);
void	ft_putnbr(int n);
int		count_number(int n);

int		ft_putnbr_count_u(unsigned int n);
void	ft_putnbr_u(unsigned int n);
int		count_number_u(unsigned int n);

int		ft_putnbr_count_x(unsigned int n);
void	ft_putnbr_x(unsigned int n);
int		count_number_x(unsigned int n);

int		ft_putnbr_count_xx(unsigned int n);
void	ft_putnbr_xx(unsigned int n);

int		ft_putnbr_count_p(unsigned long n);
void	ft_putnbr_p(unsigned long n);
int		count_number_p(unsigned long n);

#endif
