/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:00:21 by amahla            #+#    #+#             */
/*   Updated: 2022/05/04 13:17:45 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	init_charflag(t_flag *fg)
{
	fg->zero = 0;
	fg->point = 0;
	return (0);
}

char	*ft_printf_char(t_flag *fg, char c, int *len)
{
	char	*str;
	int		option;

	str = NULL;
	option = init_charflag(fg);
	fg->nbrlen = 1;
	str = ft_flag(fg, option);
	if (!str)
	{
		str = ft_calloc(fg->nbrlen + option + 1, sizeof(char));
		if (!str)
			return (NULL);
		ft_memset(str, '0', fg->nbrlen + option);
	}
	*len = ft_strlen(str);
	if (fg->minus)
		str[0] = c;
	else
		str[ft_strlen(str) - 1] = c;
	return (str);
}

char	*ft_point(t_flag *fg, char *str)
{
	char	*dst;

	dst = NULL;
	if ((size_t)(fg->precision) < ft_strlen(str))
	{
		dst = ft_strndup(str, (size_t)(fg->precision));
		free(str);
	}
	else
		dst = str;
	fg->point = 0;
	fg->precision = 0;
	return (dst);
}

int	calloc_str(char **str, int size)
{
	*str = ft_calloc(size + 1, sizeof(char));
	if (!*str)
	{
		*str = NULL;
		return (0);
	}
	else
		ft_memset(*str, ' ', size);
	return (1);
}	

char	*ft_printf_str(t_flag *fg, char *to_print)
{
	char	*str;
	char	*src;

	str = NULL;
	src = NULL;
	fg->zero = 0;
	if (!to_print)
		src = ft_strdup("(null)");
	else
		src = ft_strdup(to_print);
	if (fg->point)
		src = ft_point(fg, src);
	fg->nbrlen = ft_strlen(src);
	str = ft_flag(fg, 0);
	if (!str)
	{
		if (!calloc_str(&str, fg->nbrlen))
			return (NULL);
	}
	if (fg->minus)
		ft_memcpy(str, src, ft_strlen(src));
	else
		ft_memcpy(str + ft_strlen(str) - ft_strlen(src), src, ft_strlen(src));
	free(src);
	return (str);
}
