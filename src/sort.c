/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   sort.c                                          :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/08 00:17:18 by amahla ###       ########     ########   */
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
