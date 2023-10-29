/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:00:53 by amahla            #+#    #+#             */
/*   Updated: 2022/05/05 19:27:17 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

char	*ft_intoa(int n, char *res, int index)
{
	unsigned int	nb;

	if (n < 0)
		nb = n * -1;
	else
		nb = n;
	putnbr(nb, index + ilen(nb) - 1, res);
	return (res);
}

char	*ft_utoa(int nb, char *res, int index)
{
	putuint(nb, index + ulen(nb) - 1, res);
	return (res);
}

char	*ft_ptrtoa(unsigned long long ptr, char *res, int index)
{
	putptr(ptr, index + ptrlen(ptr) - 1, res);
	return (res);
}

char	*ft_xtoa(int n, char *res, int index)
{
	unsigned int	nb;

	if (n < 0)
		nb = UINT_MAX + 1 + n;
	else
		nb = n;
	puthex(nb, index + xlen(nb) - 1, res);
	return (res);
}

char	*let_upper(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	dest = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!dest)
		return (NULL);
	while (dest && str && *(str + i))
	{
		*(dest + i) = ft_toupper(*(str + i));
		i++;
	}
	if (str)
		free(str);
	return (dest);
}
