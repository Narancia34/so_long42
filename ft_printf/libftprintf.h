/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:25:04 by mgamraou          #+#    #+#             */
/*   Updated: 2025/01/30 15:32:40 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <stdarg.h>

int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_puthexa(unsigned int n, const char format);
int	ft_putaddress(void *ptr);
int	ft_printf(const char *formats, ...);
int	ft_putunint(unsigned int n);
int	ft_hexacount(unsigned long int n);
int	ft_digitcount(int n);

#endif
