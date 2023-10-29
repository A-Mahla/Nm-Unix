/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr_pct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:00:05 by amahla            #+#    #+#             */
/*   Updated: 2022/05/04 12:26:04 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	init_ptrflag(t_flag *fg, unsigned long long nb)
{
	fg->zero = 0;
	if (nb == 0)
		return (5);
	return (2);
}

void	ft_fill_ptr(t_flag *fg, char *str, unsigned long long nb)
{
	int	size;

	if (fg->minus)
		size = 2;
	else
		size = ft_strlen(str) - fg->nbrlen;
	if (fg->nbrlen)
		ft_ptrtoa(nb, str, size);
	if (fg->nbrlen)
	{
		str[size - 1] = 'x';
		str[size - 2] = '0';
	}
	else if (fg->minus)
		ft_memcpy(str, "(nil)", 5);
	else
		ft_memcpy(str + size - 5, "(nil)", 5);
}

char	*ft_printf_ptr(t_flag *fg, void *ptr)
{
	char				*str;
	unsigned long long	nb;
	int					option;

	str = NULL;
	nb = (unsigned long long)ptr;
	option = init_ptrflag(fg, nb);
	fg->nbrlen = ptrlen(nb);
	if (nb == 0)
		fg->nbrlen = 0;
	str = ft_flag(fg, option);
	if (!str)
	{
		str = ft_calloc(fg->nbrlen + option + 1, sizeof(char));
		if (!str)
			return (NULL);
		ft_memset(str, '0', fg->nbrlen + option);
	}
	ft_fill_ptr(fg, str, nb);
	return (str);
}

char	*ft_print_pct(void)
{
	char	*str;

	str = NULL;
	str = ft_calloc(2, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '%';
	return (str);
}
