/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:01:09 by amahla            #+#    #+#             */
/*   Updated: 2022/05/04 12:40:19 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

void	puthex(int n, int size, char *res)
{
	char			*conv;
	unsigned int	nb;

	conv = "0123456789abcdef";
	if (n < 0)
		nb = UINT_MAX + 1 + n;
	else
		nb = n;
	if (nb >= 16)
		puthex(nb / 16, size - 1, res);
	res[size] = conv[nb % 16];
}

void	putptr(unsigned long long nb, int size, char *res)
{
	char	*conv;

	conv = "0123456789abcdef";
	if (nb >= 16)
		putptr(nb / 16, size - 1, res);
	res[size] = conv[nb % 16];
}

void	putnbr(int n, int size, char *res)
{
	unsigned int	nb;

	if (n < 0)
		nb = n * -1;
	else
		nb = n;
	if (nb >= 10)
		putnbr(nb / 10, size - 1, res);
	res[size] = nb % 10 + 48;
}

void	putuint(unsigned int nb, int size, char *res)
{
	if (nb >= 10)
		putnbr(nb / 10, size - 1, res);
	res[size] = nb % 10 + 48;
}
