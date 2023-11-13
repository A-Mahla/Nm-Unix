/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/13 18:11:44 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


static void	special_char_counter(char **str, size_t *count, size_t *index, bool *check_number);
static void	tolower_counter(char *c1, char c2, size_t *upper);
static int	comparator(int8_t c1, int8_t c2);


int	ft_strcoll(char *str1, char *str2)
{
	char	c1, c2;
	size_t	i = 0, y = 0;
	size_t	f1 = 0, f2 = 0;
	size_t	upper1 = 0, upper2 = 0;
	bool	check_number = false;

	for (;str1[i] && str2[y]; i++, y++) {
		special_char_counter(&str1, &f1, &i, &check_number);
		special_char_counter(&str2, &f2, &y, &check_number);
		c1 = str1[i];
		c2 = str2[y];
		tolower_counter(&c1, c2, &upper1);
		tolower_counter(&c2, c1, &upper2);
		if (c1 != c2)
			return comparator(c1, c2);
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
	return comparator(str1[i], str2[y]);
}


static void	special_char_counter(char **str, size_t *count, size_t *index, bool *check_number)
{
	if (!*check_number && ft_isdigit((*str)[*index]) && (*str)[*index + 1] == '.')
		*check_number = true;
	while ((*str)[*index] && !ft_isalnum((*str)[*index]) && (*str)[*index] != '$') {
		if ((*str)[*index] == '/')
			*check_number = false;
		if ((*str)[*index] == '_' || (*str)[*index] == '.')
			(*count)++;
		if ((*str)[*index] == '*' && !*check_number)
			(*count)++;
		if ((*str)[*index] == ')' && *index != 0 && ft_isdigit((*str)[*index - 1]))
			(*count)--;
		(*index)++;
	}
}


static void	tolower_counter(char *c1, char c2, size_t *upper)
{
	if (*c1 >= 'A' && *c1 <= 'Z' && c2 >= 'a' && c2 <= 'z') {
		*c1 += 32;
		(*upper)++;
	}
}


void	swap_sym(struct symtab_s *sym1, struct symtab_s *sym2)
{
	struct symtab_s tmp;

	tmp.ptr = sym1->ptr;
	tmp.idx = sym1->idx;
	sym1->ptr = sym2->ptr;
	sym1->idx = sym2->idx;
	sym2->ptr = tmp.ptr;
	sym2->idx = tmp.idx;
}


static int	comparator(int8_t c1, int8_t c2)
{
	if (c1 < 0 && c2 >= 0) {
		return 1;
	} else if (c2 < 0 && c1 >= 0) {
		return -1;
	}
	return c1 - c2;

}
