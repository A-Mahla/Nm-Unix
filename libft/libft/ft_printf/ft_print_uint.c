/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:00:34 by amahla            #+#    #+#             */
/*   Updated: 2022/05/06 11:22:19 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	init_uflags(t_flag *fg)
{
	fg->hash = 0;
	fg->plus = 0;
	fg->space = 0;
	if (fg->minus)
		fg->zero = 0;
	return (0);
}

void	ft_fill_uint(t_flag *fg, char *str, int nb)
{
	int	size;

	if (fg->minus)
	{
		if (start_zero(str, fg->nbrlen) == -1)
			size = 0;
		else
			size = start_zero(str, fg->nbrlen);
	}
	else
		size = ft_strlen(str) - fg->nbrlen;
	ft_utoa(nb, str, size);
}

char	*ft_printf_uint(t_flag *fg, unsigned int nb)
{
	char	*str;
	int		option;

	str = NULL;
	fg->nbrlen = ulen(nb);
	option = init_uflags(fg);
	if (nb == 0 && fg->point && !(fg->precision))
		fg->nbrlen = 0;
	str = ft_flag(fg, option);
	if (!str && fg->nbrlen)
	{
		str = ft_calloc(fg->nbrlen + 1, sizeof(char));
		if (!str)
			return (NULL);
		ft_memset(str, ' ', fg->nbrlen);
	}
	if (fg->nbrlen)
		ft_fill_uint(fg, str, nb);
	return (str);
}
