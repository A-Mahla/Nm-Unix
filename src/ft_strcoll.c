/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   ft_strcoll.c                                    :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/08 00:14:07 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


void	underscore_counter(char **str, size_t *count, size_t *index);
void	tolower_counter(char *c1, char c2, size_t *upper);


int	ft_strcoll(char *str1, char *str2)
{
	char	c1, c2;
	size_t	i = 0, y = 0;
	size_t	f1 = 0, f2 = 0;
	size_t	upper1 = 0, upper2 = 0;

	for (;str1[i] && str2[y]; i++, y++) {
		underscore_counter(&str1, &f1, &i);
		underscore_counter(&str2, &f2, &y);
		c1 = str1[i];
		c2 = str2[y];
		tolower_counter(&c1, c2, &upper1);
		tolower_counter(&c2, c1, &upper2);
		if (c1 != c2)
			return c1 - c2;
	}
	if (str1[i] == '\0' && str2[y] == '\0') {
		if (upper1 > upper2)
			return 1;
		if (upper1 < upper2)
			return -1;
		if (f1 < f2)
			return 1;
		if (f1 > f2)
			return -1;
	}
	if (str1[i] == '_')
		return 1;
	if (str2[y] == '_')
		return -1;
	return str1[i] - str2[y];
}


void	underscore_counter(char **str, size_t *count, size_t *index)
{
	while ((*str)[*index] == '.' || (*str)[*index] == '@')
		(*index)++;
	while ((*str)[*index] == '_') {
		(*count)++;
		(*index)++;
	}
}


void	tolower_counter(char *c1, char c2, size_t *upper)
{
	if (*c1 >= 'A' && *c1 <= 'Z' && c2 >= 'a' && c2 <= 'z') {
		*c1 += 32;
		(*upper)++;
	}
}
