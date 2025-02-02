/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:32:42 by mgamraou          #+#    #+#             */
/*   Updated: 2024/11/24 17:02:51 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_formatcheck(va_list args, const char c)
{
	int	printed;

	printed = 0;
	if (c == '%')
		printed = ft_putchar('%');
	else if (c == 'c')
		printed = ft_putchar(va_arg(args, int));
	else if (c == 's')
		printed = ft_putstr(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		printed = ft_putnbr(va_arg(args, int));
	else if (c == 'x' || c == 'X')
		printed = ft_puthexa(va_arg(args, unsigned int), c);
	else if (c == 'p')
		printed = ft_putaddress(va_arg(args, void *));
	else if (c == 'u')
		printed = ft_putunint(va_arg(args, unsigned int));
	else
	{
		printed = ft_putchar('%');
		printed = ft_putchar(c);
	}
	return (printed);
}

int	ft_checkparam(const char *formats, va_list args)
{
	int	i;
	int	printed;

	i = 0;
	printed = 0;
	while (formats[i])
	{
		if (formats[i] == '%' && formats[i + 1] != '\0')
		{
			i++;
			printed += ft_formatcheck(args, formats[i]);
		}
		else if (formats[i] == '%' && formats[i + 1] == '\0')
		{
			va_end(args);
			return (-1);
		}
		else
			printed += ft_putchar(formats[i]);
		i++;
	}
	va_end(args);
	return (printed);
}

int	ft_printf(const char *formats, ...)
{
	va_list	args;

	if (formats == NULL || write(1, NULL, 0) == -1)
		return (-1);
	va_start(args, formats);
	return (ft_checkparam(formats, args));
}
