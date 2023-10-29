/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                    :+:       :+: :+: :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:59:27 by amahla            #+#    #+#             */
/*   Updated: 2023/10/29 22:41:46 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	fprocess_print(int fd, va_list ap, char c, t_flag *fg)
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
	ft_putstr_len(fd, str, len);
	init_flag(fg);
	if (str)
		free(str);
	return (len);
}

void	fprocess(int fd, va_list ap, char *str, int *count)
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
				*count = *count + fprocess_print(fd, ap, *(str + i++), &fg);
		}
		else
		{
			write(1, str + i++, 1);
			(*count)++;
		}
	}
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, format);
	fprocess(fd, ap, (char *)format, &count);
	va_end(ap);
	return (count);
}
