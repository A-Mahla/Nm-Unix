/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   sort.c                                          :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/06 04:11:21 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"



void	swap_ptr(void **ptr1, void **ptr2);
int		ft_strcoll(char *str1, char *str2);
void	underscore_counter(char **str, size_t *count, size_t *index);
void	tolower_coll(char *c1, char c2, size_t *upper);
void	quicksort64(char *strtab, Elf64_Sym **symbol, size_t begin, size_t end);
size_t	size_symtab64(Elf64_Sym **symtab);


void	sort(struct filedata_s *binary)
{
	Elf64_Sym	**symtab64 = NULL;
	Elf32_Sym	**symtab32 = NULL;
	char		*strtab = binary->strtab;

	if (binary->ei_class == ELFCLASS64) {
		symtab64 = (Elf64_Sym **)binary->symtab;
		quicksort64(strtab, symtab64, 0, size_symtab64(symtab64) - 1);
//		for (size_t i = 0;  symtab64[i]; i++) {
//			for (size_t y = i + 1;  symtab64[y]; y++) {
//				if (ft_strcoll(strtab + symtab64[i]->st_name, strtab + symtab64[y]->st_name) > 0)
//					swap_ptr((void *)(symtab64 + i), (void *)(symtab64 + y));
//			}
//		}
	} else if (binary->ei_class == ELFCLASS32) {
		symtab32 = (Elf32_Sym **)binary->symtab;
		for (size_t i = 0;  symtab32[i]; i++) {
			for (size_t y = i + 1;  symtab32[y]; y++) {
				if (ft_strcoll(strtab + symtab32[i]->st_name, strtab + symtab32[y]->st_name) > 0)
					swap_ptr((void *)(symtab32 + i), (void *)(symtab32 + y));
			}
		}
	}
}


size_t	size_symtab64(Elf64_Sym **symtab)
{
	size_t	count = 0;

	while(symtab[count])
		count++;
	return count;
}


size_t	partition64(char *strtab, Elf64_Sym **symtab, size_t begin, size_t end)
{
	Elf64_Sym	*pivot = symtab[end];
	int			i = begin;
	int			ret;
	bool		start = true;

	for(size_t y = begin; y < end; y++) {
		if ((ret = ft_strcoll(strtab + symtab[y]->st_name, strtab + pivot->st_name)) < 0
			|| (ret == 0 && symtab[y]->st_value < pivot->st_value)) {
			if (!start)
				i++;
			else
				start = false;
			swap_ptr((void *)(symtab + i), (void *)(symtab + y));
		}
	}
	if (!start)
		i++;
	swap_ptr((void *)(symtab + i), (void *)(symtab + end));
	return i;
}


void	quicksort64(char *strtab, Elf64_Sym **symtab, size_t begin, size_t end)
{
	int	pivot;

	if (begin < end) {
		pivot = partition64(strtab, symtab, begin, end);
		quicksort64(strtab, symtab, begin, pivot - 1);
		quicksort64(strtab, symtab, pivot + 1, end);
	}
}



int	ft_strcoll(char *str1, char *str2)
{
	char	c1, c2;
	size_t	i = 0, y = 0;
	size_t	f1 = 0, f2 = 0;
	size_t	upper1 = 0, upper2 = 0;

	underscore_counter(&str1, &f1, &i);
	underscore_counter(&str2, &f2, &y);
	c1 = str1[i];
	c2 = str2[y];
	while (str1[i++] && str2[y++]) {
		tolower_coll(&c1, c2, &upper1);
		tolower_coll(&c2, c1, &upper2);
		if (c1 != c2 )
			break;
		underscore_counter(&str1, &f1, &i);
		underscore_counter(&str2, &f2, &y);
//		while (str1[i] == '_')
//			i++;
//		while (str2[y] == '_')
//			y++;
		c1 = str1[i];
		c2 = str2[y];
	}
	if (c1 == '\0' && c2 == '\0' && (f1 < f2 || upper1 > upper2))
		return 1;
	if (c1 == '\0' && c2 == '\0' && (f1 > f2 || upper1 < upper2))
		return -1;
	if (c1 == '@')
		return 1;
	if (c2 == '@')
		return -1;
//	if (c1 == '_')
//		return 1;
//	if (c2 == '_')
//		return -1;
	return c1 - c2;
}


void	underscore_counter(char **str, size_t *count, size_t *index)
{
	while ((*str)[*index] && (*str)[*index] == '.')
		(*index)++;
	while ((*str)[*index] && (*str)[*index] == '_') {
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


void	swap_ptr(void **ptr1, void **ptr2)
{
	void	*tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}
