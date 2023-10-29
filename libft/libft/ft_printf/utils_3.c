/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                       :+:       :+: :+: :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:01:01 by amahla            #+#    #+#             */
/*   Updated: 2023/10/29 22:36:41 by amahla ###       ########     ########   */
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

void	ft_putstr_len(int fd, char *str, int len)
{
	int	i;

	i = 0;
	while (str && i < len)
		write(fd, str + i++, 1);
}
