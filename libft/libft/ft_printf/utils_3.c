/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:01:01 by amahla            #+#    #+#             */
/*   Updated: 2022/05/04 12:40:12 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	ulen(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	ilen(int n)
{
	unsigned int	nb;
	int				i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		nb = n * -1;
	else
		nb = n;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	xlen(int n)
{
	unsigned int	nb;
	int				i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		nb = UINT_MAX + 1 + n;
	else
		nb = n;
	while (nb > 0)
	{
		nb = nb / 16;
		i++;
	}
	return (i);
}

int	ptrlen(unsigned long long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 16;
		i++;
	}
	return (i);
}

void	ft_putstr_len(char *str, int len)
{
	int	i;

	i = 0;
	while (str && i < len)
		write(1, str + i++, 1);
}
