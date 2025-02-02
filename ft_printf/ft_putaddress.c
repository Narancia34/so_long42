/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:07:29 by mgamraou          #+#    #+#             */
/*   Updated: 2024/11/21 11:34:05 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_convert(unsigned long int n)
{
	if (n >= 16)
	{
		ft_convert (n / 16);
		ft_convert (n % 16);
	}
	else
	{
		if (n <= 9)
			ft_putchar((n + '0'));
		else
			ft_putchar(((n - 10) + 'a'));
	}
}

int	ft_putaddress(void *ptr)
{
	int					printed;
	unsigned long int	cast;

	if (ptr == NULL)
		return (ft_printf("(nil)"));
	printed = 0;
	cast = (unsigned long int)ptr;
	printed = ft_hexacount(cast);
	ft_putstr("0x");
	printed += 2;
	ft_convert(cast);
	return (printed);
}
