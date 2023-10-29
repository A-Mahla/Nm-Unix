/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                    :+:       :+: :+: :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:56:00 by amahla            #+#    #+#             */
/*   Updated: 2023/06/24 01:37:45 by ammah ###       ########     ########    */
/*                                                                            */
/* ************************************************************************** */

#include"ft_getline.h"

char	*ft_getline(int fd)
{
	static char		*save[1024];
	char			*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = ft_str_temp(save[fd], fd);
	if (!save[fd])
		return (NULL);
	line = ft_str_to_print(save[fd]);
	save[fd] = ft_str_to_save(save[fd]);
	return (line);
}
