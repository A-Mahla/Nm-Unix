/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:59:44 by amahla            #+#    #+#             */
/*   Updated: 2022/05/04 12:24:02 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	init_xflags(t_flag *fg, int nb)
{
	int	option;

	option = 0;
	if (fg->minus)
		fg->zero = 0;
	if (fg->hash && nb != 0)
		option = 2;
	return (option);
}

void	ft_fill_hex_option(t_flag *fg, char *str, int nb, int option)
{
	int	size;

	if (fg->minus)
		size = 0;
	else
	{
		if (end_zero(str) == -1)
			size = ft_strlen(str) - fg->nbrlen - 2;
		else if ((fg->width > fg->precision && fg->point
				&& fg->width > fg->nbrlen)
			|| (!(fg->point) && !(fg->zero) && fg->width > fg->nbrlen + option))
			size = end_zero(str) - 2;
		else
			size = end_zero(str);
	}
	if (fg->hash && nb != 0)
	{
		str[size + 1] = 'x';
		str[size] = '0';
	}
}

void	ft_fill_hex(t_flag *fg, char *str, int nb, int option)
{
	int	size;

	if (fg->minus)
	{
		if (start_zero(str, fg->nbrlen) == -1)
			size = 0 + option;
		else
			size = start_zero(str, fg->nbrlen);
	}
	else
		size = ft_strlen(str) - fg->nbrlen;
	ft_xtoa(nb, str, size);
}

char	*ft_printf_hex(t_flag *fg, int nb, char c)
{
	char	*str;
	int		option;

	str = NULL;
	fg->nbrlen = xlen(nb);
	option = init_xflags(fg, nb);
	if (nb == 0 && fg->point && !(fg->precision))
		fg->nbrlen = 0;
	str = ft_flag(fg, option);
	if (!str)
	{
		str = ft_calloc(fg->nbrlen + option + 1, sizeof(char));
		if (!str)
			return (NULL);
		ft_memset(str, '0', fg->nbrlen + option);
	}
	if (fg->nbrlen)
		ft_fill_hex(fg, str, nb, option);
	ft_fill_hex_option(fg, str, nb, option);
	if (c == 'X')
		str = let_upper(str);
	return (str);
}
