/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   sort.c                                          :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/07 00:38:36 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"



void	swap_sym64(struct symtab_s *sym1, struct symtab_s *sym2);
int		ft_strcoll(char *str1, char *str2);
void	underscore_counter(char **str, size_t *count, size_t *index);
void	tolower_coll(char *c1, char c2, size_t *upper);
void	quicksort64(char *strtab, struct symtab_s *symtab, size_t begin, size_t end);
size_t	size_symtab64(struct symtab_s *symtab);


void	sort(struct filedata_s *binary)
{
	struct symtab_s	*symtab64 = NULL;
//	Elf32_Sym	**symtab32 = NULL;
	char		*strtab = binary->strtab;

	if (binary->ei_class == ELFCLASS64) {
		symtab64 = (struct symtab_s *)binary->symtab;
		quicksort64(strtab, symtab64, 0, size_symtab64(symtab64) - 1);
//		for (size_t i = 0;  symtab64[i]; i++) {
//			for (size_t y = i + 1;  symtab64[y]; y++) {
//				if (ft_strcoll(strtab + symtab64[i]->st_name, strtab + symtab64[y]->st_name) > 0)
//					swap_ptr((void *)(symtab64 + i), (void *)(symtab64 + y));
//			}
//		}
	}// else if (binary->ei_class == ELFCLASS32) {
//		symtab32 = (Elf32_Sym **)binary->symtab->ptr;
//		for (size_t i = 0;  symtab32[i]; i++) {
//			for (size_t y = i + 1;  symtab32[y]; y++) {
//				if (ft_strcoll(strtab + symtab32[i]->st_name, strtab + symtab32[y]->st_name) > 0)
//					swap_ptr((void *)(symtab32 + i), (void *)(symtab32 + y));
//			}
//		}
//	}
}


size_t	size_symtab64(struct symtab_s *symtab)
{
	size_t	count = 0;

	while(symtab[count].ptr)
		count++;
	return count;
}


size_t	partition64(char *strtab, struct symtab_s *symtab, size_t begin, size_t end)
{
	struct symtab_s	pivot = symtab[end];
	int				i = begin;
	int				ret;
	bool			start = true;

	for(size_t y = begin; y < end; y++) {
		if ((ret = ft_strcoll(strtab + symtab[y].ptr->st_name, strtab + pivot.ptr->st_name)) < 0
			|| (ret == 0 && symtab[y].idx < pivot.idx)) {
			if (!start)
				i++;
			else
				start = false;
			swap_sym64(symtab + i, symtab + y);
		}
	}
	if (!start)
		i++;
	swap_sym64(symtab + i, symtab + end);
	return i;
}


void	quicksort64(char *strtab, struct symtab_s *symtab, size_t begin, size_t end)
{
	int	pivot;

	if (begin < end) {
		pivot = partition64(strtab, symtab, begin, end);
		quicksort64(strtab, symtab, begin, pivot - 1);
		quicksort64(strtab, symtab, pivot + 1, end);
	}
}

// TO DELETE
void	testing(void)
{
	ft_printf("%d\n", ft_strcoll("d2i_EC_PRIVATEKEY", "d2i_ECPrivateKey"));
}
//


int	ft_strcoll(char *str1, char *str2)
{
	char	c1, c2;
	size_t	i = 0, y = 0;
	size_t	f1 = 0, f2 = 0;
	size_t	upper1 = 0, upper2 = 0;

	underscore_counter(&str1, &f1, &i);
	underscore_counter(&str2, &f2, &y);
	for (;str1[i] && str2[y]; i++, y++) {
		underscore_counter(&str1, &f1, &i);
		underscore_counter(&str2, &f2, &y);
		c1 = str1[i];
		c2 = str2[y];
		tolower_coll(&c1, c2, &upper1);
		tolower_coll(&c2, c1, &upper2);
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


void	tolower_coll(char *c1, char c2, size_t *upper)
{
	if (*c1 >= 'A' && *c1 <= 'Z' && c2 >= 'a' && c2 <= 'z') {
		*c1 += 32;
		(*upper)++;
	}
}


void	swap_sym64(struct symtab_s *sym1, struct symtab_s *sym2)
{
	struct symtab_s tmp;

	tmp.ptr = sym1->ptr;
	tmp.idx = sym1->idx;
	sym1->ptr = sym2->ptr;
	sym1->idx = sym2->idx;
	sym2->ptr = tmp.ptr;
	sym2->idx = tmp.idx;
}
