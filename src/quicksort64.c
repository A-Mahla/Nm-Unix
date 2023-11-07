/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   quicksort64.c                                   :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/08 00:30:34 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


void	swap_sym64(struct symtab_s *sym1, struct symtab_s *sym2);
size_t	partition64(char *strtab, struct symtab_s *symtab, size_t begin, size_t end);


void	quicksort64(char *strtab, struct symtab_s *symtab, size_t begin, size_t end)
{
	int	pivot;

	if (begin < end) {
		pivot = partition64(strtab, symtab, begin, end);
		quicksort64(strtab, symtab, begin, pivot - 1);
		quicksort64(strtab, symtab, pivot + 1, end);
	}
}


size_t	partition64(char *strtab, struct symtab_s *symtab, size_t begin, size_t end)
{
	struct symtab_s	pivot = symtab[end];
	int64_t			i = begin - 1;
	int8_t			ret;

	for(size_t y = begin; y < end; y++) {
		if ((ret = ft_strcoll(strtab + symtab[y].ptr->st_name, strtab + pivot.ptr->st_name)) < 0
			|| (ret == 0 && symtab[y].idx < pivot.idx)) {
			i++;
			swap_sym64(symtab + i, symtab + y);
		}
	}
	i++;
	swap_sym64(symtab + i, symtab + end);
	return i;
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
