/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline_utils1.c                             :+:       :+: :+: :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:55:24 by amahla            #+#    #+#             */
/*   Updated: 2023/06/24 01:44:52 by ammah ###       ########     ########    */
/*                                                                            */
/* ************************************************************************** */

#include"ft_getline.h"

char	*ft_str_to_save(char *save)
{
	int		i;
	int		j;
	char	*temp;

	j = 0;
	i = 0;
	while (*(save + i) && *(save + i) != '\n')
		i++;
	if (*(save + i) == '\n')
		i++;
	temp = calloc_gl(ft_strlen_gl(save + i) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (*(save + i))
		*(temp + j++) = *(save + i++);
	free(save);
	if (!ft_strlen_gl(temp))
	{
		free(temp);
		temp = NULL;
	}
	return (temp);
}

char	*ft_str_to_print(char *save)
{
	int		i;
	int		j;
	int		size;
	char	*line;

	i = 0;
	j = 0;
	size = 0;
	while (*(save + size) && *(save + size) != '\n')
		size++;
	if (*(save + size) == '\n')
		size++;
	line = calloc_gl(size + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (*(save + i) && *(save + i) != '\n')
		*(line + j++) = *(save + i++);
	if (*(save + i) == '\n')
		*(line + j) = *(save + i);
	if (!ft_strlen_gl(line))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*ft_str_temp(char *save, int fd)
{
	int		rd;
	char	*buffer;

	rd = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (buffer && rd > 0 && !ft_strchr_gl(save))
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[rd] = '\0';
		save = ft_strjoin_gl(save, buffer);
	}
	if (buffer)
		free(buffer);
	return (save);
}
