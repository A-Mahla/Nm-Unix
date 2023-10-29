/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:59:27 by amahla            #+#    #+#             */
/*   Updated: 2022/05/03 14:22:39 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

void	init_flag(t_flag *fg)
{
	fg->minus = 0;
	fg->zero = 0;
	fg->point = 0;
	fg->hash = 0;
	fg->space = 0;
	fg->plus = 0;
	fg->width = 0;
	fg->precision = 0;
	fg->nbrlen = 0;
}

int	process_print(va_list ap, char c, t_flag *fg)
{
	char	*str;
	int		len;

	len = 0;
	if (c == 'c')
		str = ft_printf_char(fg, va_arg(ap, int), &len);
	else if (c == 's')
		str = ft_printf_str(fg, va_arg(ap, char *));
	else if (c == 'p')
		str = ft_printf_ptr(fg, va_arg(ap, void *));
	else if (c == 'd' || c == 'i')
		str = ft_printf_int(fg, va_arg(ap, int));
	else if (c == 'u')
		str = ft_printf_uint(fg, va_arg(ap, unsigned int));
	else if (c == 'x' || c == 'X')
		str = ft_printf_hex(fg, va_arg(ap, int), c);
	else
		str = ft_print_pct();
	if (!len)
		len = ft_strlen(str);
	ft_putstr_len(str, len);
	init_flag(fg);
	if (str)
		free(str);
	return (len);
}

void	process_format(char *str, t_flag *fg, int i)
{
	while (is_flag(*(str + i)) || ft_isdigit(*(str + i)))
	{
		if (*(str + i) == '-')
			fg->minus = 1;
		else if (*(str + i) == '0')
			fg->zero = 1;
		else if (*(str + i) == '.')
			fg->point = 1;
		else if (*(str + i) == '#')
			fg->hash = 2;
		else if (*(str + i) == ' ')
			fg->space = 1;
		else if (*(str + i) == '+')
			fg->plus = 1;
		if (is_flag(*(str + i)))
			i++;
		if (ft_isdigit(*(str + i)) && *(str + i - 1) == '.')
			fg->precision = ft_atoi(str + i);
		else if (*(str + i) >= '1' && *(str + i) <= '9')
			fg->width = ft_atoi(str + i);
		if (*(str + i) != '0')
			while (*(str + i) && ft_isdigit(*(str + i)))
				i++;
	}
}

void	process(va_list ap, char *str, int *count)
{
	int		i;
	int		y;
	t_flag	fg;

	i = 0;
	init_flag(&fg);
	while (*(str + i))
	{
		y = 0;
		if (*(str + i) == '%')
		{
			process_format(str + ++i, &fg, y);
			while (*(str + i) && !is_conv(str[i]))
				i++;
			if (*(str + i) && is_conv(str[i]))
				*count = *count + process_print(ap, *(str + i++), &fg);
		}
		else
		{
			write(1, str + i++, 1);
			(*count)++;
		}
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, format);
	process(ap, (char *)format, &count);
	va_end(ap);
	return (count);
}
