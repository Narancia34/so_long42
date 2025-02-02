/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:07:42 by mgamraou          #+#    #+#             */
/*   Updated: 2024/11/21 11:34:12 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_hexacount(unsigned long int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

int	ft_puthexa(unsigned int n, const char format)
{
	if (n == 0)
	{
		ft_putchar(0 + '0');
		return (1);
	}
	if (n >= 16)
	{
		ft_puthexa (n / 16, format);
		ft_puthexa (n % 16, format);
	}
	else
	{
		if (n <= 9)
			ft_putchar((n + '0'));
		else
		{
			if (format == 'x')
				ft_putchar(((n - 10) + 'a'));
			else if (format == 'X')
				ft_putchar(((n - 10) + 'A'));
		}
	}
	return (ft_hexacount(n));
}
