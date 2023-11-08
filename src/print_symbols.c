/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   print_symbols.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/05 02:37:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/08 19:06:13 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


static void	print_symbol64(struct symtab_s *symtab, struct filedata_s *binary);
static void	print_symbol32(struct symtab_s *symtab, struct filedata_s *binary);


void	print_symbols(struct filedata_s *binary)
{
	if (binary->ei_class == ELFCLASS64)
		print_symbol64(binary->symtab, binary);
	else if (binary->ei_class == ELFCLASS32)
		print_symbol32(binary->symtab, binary);
}


static void	print_symbol64(struct symtab_s *symtab, struct filedata_s *binary)
{
	Elf64_Sym		*sym64 = NULL;
	char			c;

	for	(size_t i = 0; symtab[i].ptr; i++) {
		sym64 = (Elf64_Sym *)symtab[i].ptr;
		c = find_letter64(sym64, (Elf64_Ehdr *)binary->file);
		if (c != 'U' && c != 'v' && c != 'w')
			ft_printf("%016x", sym64->st_value); 
		else
			ft_printf("                ");
		ft_printf(" %c ", c); 
		ft_printf("%s\n", binary->strtab + sym64->st_name);
	}
}


static void	print_symbol32(struct symtab_s *symtab, struct filedata_s *binary)
{
	Elf32_Sym		*sym32 = NULL;
	char			c;

	for	(size_t i = 0; symtab[i].ptr; i++) {
		sym32 = (Elf32_Sym *)symtab[i].ptr;
		c = find_letter32(sym32, (Elf32_Ehdr *)binary->file);
		if (c != 'U' && c != 'v' && c != 'w')
			ft_printf("%08x", sym32->st_value); 
		else
			ft_printf("        ");
		ft_printf(" %c ", c); 
		ft_printf("%s\n", binary->strtab + sym32->st_name);
	}
}
