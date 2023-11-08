/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   quicksort64.c                                   :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/08 16:59:27 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


static size_t	partition(char *strtab, struct symtab_s *symtab, size_t begin, size_t end)
{
	struct symtab_s	pivot = symtab[end];
	Elf64_Sym		*sym = NULL;
	Elf64_Sym		*sym_pivot = (Elf64_Sym *)pivot.ptr;
	int64_t			i = begin - 1;
	int8_t			ret;

	for(size_t y = begin; y < end; y++) {
		sym = (Elf64_Sym *)symtab[y].ptr;
		if ((ret = ft_strcoll(strtab + sym->st_name, strtab + sym_pivot->st_name)) < 0
			|| (ret == 0 && symtab[y].idx < pivot.idx)) {
			i++;
			swap_sym(symtab + i, symtab + y);
		}
	}
	i++;
	swap_sym(symtab + i, symtab + end);
	return i;
}


void	quicksort64(char *strtab, struct symtab_s *symtab, size_t begin, size_t end)
{
	int	pivot;

	if (begin < end) {
		pivot = partition(strtab, symtab, begin, end);
		quicksort64(strtab, symtab, begin, pivot - 1);
		quicksort64(strtab, symtab, pivot + 1, end);
	}
}
