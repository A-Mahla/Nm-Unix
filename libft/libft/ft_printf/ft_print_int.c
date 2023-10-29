/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:59:53 by amahla            #+#    #+#             */
/*   Updated: 2022/05/04 12:24:49 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	init_iflags(t_flag *fg, int nb)
{
	int	option;

	option = 0;
	if (fg->plus)
		fg->space = 0;
	if (fg->minus)
		fg->zero = 0;
	if ((fg->plus && nb >= 0) || (fg->space && nb >= 0) || nb < 0)
		option = 1;
	return (option);
}

void	ft_fill_int_option(t_flag *fg, char *str, int nb, int option)
{
	int	size;

	if (fg->minus)
		size = 0;
	else
	{
		if (end_zero(str) == -1)
			size = ft_strlen(str) - fg->nbrlen - 1;
		else if ((fg->width > fg->precision && fg->point
				&& fg->width > fg->nbrlen)
			|| (!(fg->point) && (!fg->zero) && fg->width > fg->nbrlen + option))
			size = end_zero(str) - 1;
		else
			size = end_zero(str);
	}
	if (nb < 0)
		str[size] = '-';
	else if (fg->space && nb >= 0)
		str[size] = ' ';
	else if (fg->plus && nb >= 0)
		str[size] = '+';
}

void	ft_fill_int(t_flag *fg, char *str, int nb, int option)
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
	ft_intoa(nb, str, size);
}

char	*ft_printf_int(t_flag *fg, int nb)
{
	char	*str;
	int		option;

	str = NULL;
	fg->nbrlen = ilen(nb);
	option = init_iflags(fg, nb);
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
		ft_fill_int(fg, str, nb, option);
	ft_fill_int_option(fg, str, nb, option);
	return (str);
}
