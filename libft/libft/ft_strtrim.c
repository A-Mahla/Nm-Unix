/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:36:57 by amahla            #+#    #+#             */
/*   Updated: 2022/05/02 12:36:59 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static size_t	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set && *(set + i))
	{
		if (c == *(set + i++))
			return (1);
	}
	return (0);
}

static size_t	slen(char const *str)
{
	size_t	i;

	i = 0;
	while (str && *(str + i))
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	size_t	i;
	size_t	size;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (is_set(*s1, set))
		s1++;
	size = slen(s1);
	while (size != 0 && is_set(*(s1 + size - 1), set))
		size--;
	dst = malloc((size + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (*(s1 + i) && i < size)
	{
		*(dst + i) = *(s1 + i);
		i++;
	}
	*(dst + i) = '\0';
	return (dst);
}
