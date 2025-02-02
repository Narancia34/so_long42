/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:59:26 by mgamraou          #+#    #+#             */
/*   Updated: 2024/11/21 11:34:19 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putunint(unsigned int n)
{
	unsigned int	nb;
	int				i;

	nb = n;
	i = 0;
	if (n == 0)
	{
		ft_putchar(0 + '0');
		return (1);
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	if (n > 9)
	{
		ft_putunint(n / 10);
		ft_putchar((n % 10) + '0');
	}
	else if (n <= 9)
		ft_putchar((n % 10) + '0');
	return (i);
}
