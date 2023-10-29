/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                 :+:       :+: :+: :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:55:30 by amahla            #+#    #+#             */
/*   Updated: 2023/06/24 01:39:56 by ammah ###       ########     ########    */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETLINE_H
# define FT_GETLINE_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 32

//		ft_getline.c
char	*ft_getline(int fd);

//		ft_getline_utils1.c
char	*ft_str_to_save(char *save);
char	*ft_str_to_print(char *save);
char	*ft_str_temp(char *save, int fd);

//		ft_getline_utils2.c
void	*calloc_gl(size_t count, size_t size);
char	*ft_strjoin_gl(char *s1, char *s2);
int		ft_strlen_gl(char const *str);
int		ft_strchr_gl(char *str);

#endif
