/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:59:14 by amahla            #+#    #+#             */
/*   Updated: 2022/05/04 12:22:55 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

char	*ft_flag_zero(t_flag *fg, int option)
{
	char	*new;

	new = NULL;
	if (fg->zero && !(fg->point) && fg->width > fg->nbrlen + option)
	{
		new = ft_calloc(fg->width + 1, sizeof(char));
		if (!new)
			return (NULL);
		ft_memset(new, '0', fg->width);
	}
	return (new);
}

void	ft_flag_point(t_flag *fg, char **str, int option)
{
	if (*str && !(fg->minus) && fg->point && fg->precision > fg->nbrlen)
		ft_memset(*str + ft_strlen(*str) - fg->precision, '0', fg->precision);
	else if (*str && fg->minus && fg->point && fg->precision > fg->nbrlen)
		ft_memset(*str, '0', fg->precision + option);
	else if (!*str && fg->point && fg->precision > fg->nbrlen)
	{
		*str = ft_calloc(fg->precision + option + 1, sizeof(char));
		if (!*str)
		{
			*str = NULL;
			return ;
		}	
		ft_memset(*str, '0', fg->precision + option);
	}
}

char	*ft_flag(t_flag *fg, int option)
{
	char	*str;

	str = NULL;
	if (fg->zero)
		str = ft_flag_zero(fg, option);
	if (!str && fg->width > fg->precision
		&& fg->width > fg->nbrlen + option)
	{
		str = ft_calloc(fg->width + 1, sizeof(char));
		if (!str)
			return (NULL);
		ft_memset(str, ' ', fg->width);
	}
	if (fg->point)
		ft_flag_point(fg, &str, option);
	return (str);
}
