/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:58:17 by mgamraou          #+#    #+#             */
/*   Updated: 2024/11/21 11:34:15 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_digitcount(int n)
{
	long	nb;
	int		count;

	nb = n;
	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		count++;
	}
	while (nb > 0)
	{
		count++;
		nb = nb / 10;
	}
	return (count);
}

int	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putchar((nb % 10 + '0'));
	}
	else
		ft_putchar((nb + '0'));
	return (ft_digitcount(n));
}
