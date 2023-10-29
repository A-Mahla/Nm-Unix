/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:27:43 by amahla            #+#    #+#             */
/*   Updated: 2022/05/03 10:49:44 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dst;
	size_t	i;

	i = 0;
	dst = malloc(nmemb * size);
	if (!dst)
		return (NULL);
	while (i < nmemb * size)
		*((unsigned char *)dst + i++) = 0;
	return (dst);
}
