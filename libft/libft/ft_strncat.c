/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:12:54 by amahla            #+#    #+#             */
/*   Updated: 2022/03/14 14:44:11 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dest && *(dest + i))
		i++;
	while (src && *(src + j) && j < nb)
	{
		*(dest + i + j) = *(src + j);
		j++;
	}
	if (i + j < nb)
		*(dest + j) = '\0';
	return (dest);
}
