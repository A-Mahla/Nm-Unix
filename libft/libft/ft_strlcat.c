/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:35:14 by amahla            #+#    #+#             */
/*   Updated: 2022/05/02 12:35:17 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*(dst + i))
		i++;
	while (*(src + j) && i + j + 1 < dstsize)
	{
		*(dst + i + j) = *(src + j);
		j++;
	}
	if (i + j < dstsize)
		*(dst + i + j) = '\0';
	while (*(src + j))
		j++;
	if (i > dstsize)
		i = dstsize;
	return (i + j);
}
