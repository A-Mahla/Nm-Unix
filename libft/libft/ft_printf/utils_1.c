/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:00:42 by amahla            #+#    #+#             */
/*   Updated: 2022/05/02 13:00:45 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	is_flag(char c)
{
	if (c == '#' || c == ' ' || c == '+' || c == '-' || c == '0' || c == '.')
		return (1);
	return (0);
}

int	is_conv(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

char	*ft_strndup(char *s1, size_t n)
{
	char	*dst;
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (*(s1 + i))
	{
		size++;
		i++;
	}
	dst = malloc((size + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < size && i < n)
	{
		*(dst + i) = *(s1 + i);
		i++;
	}
	*(dst + i) = '\0';
	return (dst);
}

int	start_zero(char *str, int nbrlen)
{
	int	i;

	i = 0;
	while (*(str + i) && *(str + i) == '0')
		i++;
	if (i == 0)
		return (-1);
	i = i - nbrlen;
	return (i);
}

int	end_zero(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_isalnum(*(str + i)))
		i--;
	i++;
	if ((size_t)i == ft_strlen(str) - 1)
		return (-1);
	return (i);
}
