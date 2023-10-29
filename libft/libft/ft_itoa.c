/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:28:54 by amahla            #+#    #+#             */
/*   Updated: 2022/05/02 12:28:56 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	nblen(unsigned int nb)
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

static void	putnbr_itoa(unsigned int nb, int size, char *res)
{
	if (nb >= 10)
		putnbr_itoa(nb / 10, size - 1, res);
	res[size] = nb % 10 + 48;
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	int				size;
	int				sign;
	char			*res;

	size = 0;
	sign = 0;
	if (n < 0)
	{
		sign++;
		nb = n * -1;
	}
	else
		nb = n;
	size = nblen(nb);
	res = malloc((size + sign + 1) * sizeof(char));
	if (!res)
		return (NULL);
	putnbr_itoa(nb, size - 1 + sign, res);
	if (sign)
		res[0] = '-';
	res[size + sign] = '\0';
	return (res);
}
