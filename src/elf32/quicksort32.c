/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   quicksort32.c                                   :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/08 01:24:41 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


size_t	partition32(char *strtab, struct symtab_s *symtab, size_t begin, size_t end)
{
	struct symtab_s	pivot = symtab[end];
	Elf32_Sym		*sym = NULL;
	Elf32_Sym		*sym_pivot = (Elf32_Sym *)pivot.ptr;
	int32_t			i = begin - 1;
	int8_t			ret;

	for(size_t y = begin; y < end; y++) {
		sym = (Elf32_Sym *)symtab[y].ptr;
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


void	quicksort32(char *strtab, struct symtab_s *symtab, size_t begin, size_t end)
{
	int	pivot;

	if (begin < end) {
		pivot = partition32(strtab, symtab, begin, end);
		quicksort32(strtab, symtab, begin, pivot - 1);
		quicksort32(strtab, symtab, pivot + 1, end);
	}
}
