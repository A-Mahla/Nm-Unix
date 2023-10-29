/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                     :+:       :+: :+: :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:01:30 by amahla            #+#    #+#             */
/*   Updated: 2023/10/29 22:42:00 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"

typedef struct s_flag
{
	int	minus;
	int	zero;
	int	point;
	int	hash;
	int	space;
	int	plus;
	int	width;
	int	precision;
	int	nbrlen;
}				t_flag;

//		ft_printf.c
void	init_flag(t_flag *fg);
void	process_format(char *str, t_flag *fg, int i);
int		ft_printf(const char *format, ...);

//		ft_dprintf.c
int		ft_dprintf(int fd, const char *format, ...);

//		ft_print_str_char.c
char	*ft_printf_char(t_flag *fg, char c, int	*len);
char	*ft_printf_str(t_flag *fg, char *to_print);

//		ft_print_ptr_pct.c
char	*ft_printf_ptr(t_flag *fg, void *ptr);
char	*ft_print_pct(void);

//		ft_print_hex.c
char	*ft_printf_hex(t_flag *fg, int nb, char c);

//		ft_print_int.c
char	*ft_printf_int(t_flag *fg, int nb);

//		ft_print_uint.c
char	*ft_printf_uint(t_flag *fg, unsigned int nb);

//		ft_flag.c
char	*ft_flag(t_flag *fg, int option);

//		utils_1.c
int		is_conv(char c);
int		is_flag(char c);
char	*ft_strndup(char *s1, size_t n);
int		start_zero(char *str, int nbrlen);
int		end_zero(char *str);

//		utils_2.c
char	*ft_intoa(int n, char *res, int index);
char	*ft_utoa(int nb, char *res, int index);
char	*ft_ptrtoa(unsigned long long ptr, char *res, int index);
char	*ft_xtoa(int n, char *res, int index);
char	*let_upper(char *str);

//		utils_3.c
int		ulen(unsigned int nb);
int		ilen(int n);
int		xlen(int n);
int		ptrlen(unsigned long long nb);
void	ft_putstr_len(int fd, char *str, int len);

//		utils_4.c
void	puthex(int nb, int size, char *res);
void	putptr(unsigned long long nb, int size, char *res);
void	putnbr(int n, int size, char *res);
void	putuint(unsigned int nb, int size, char *res);
void	puthhex(int n, int size, char *res);

#endif
