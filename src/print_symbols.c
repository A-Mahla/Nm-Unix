/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   print_symbols.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/05 02:37:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/06 17:34:42 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


void	which_type(unsigned char type);
void	which_bind(unsigned char bind);
void	which_other(unsigned char other);
void	which_shtype(int type);

char	print_letter64(Elf64_Sym *sym, Elf64_Ehdr *ehdr);


void	print_symbols(struct filedata_s *binary)
{
	Elf64_Sym	**symtab = (Elf64_Sym **)binary->symtab;
	char		c;

	for	(size_t i= 0; symtab[i]; i++) {
		c = print_letter64(symtab[i], (Elf64_Ehdr *)binary->file);
		if (c != 'U' && c != 'v' && c != 'w')
			ft_printf("%016x", symtab[i]->st_value); 
		else
			ft_printf("                ");
		ft_printf(" %c ", c); 
		ft_printf("%s\n", binary->strtab + symtab[i]->st_name);
	}
}


char	print_letter64(Elf64_Sym *sym, Elf64_Ehdr *ehdr)
{
	Elf64_Shdr	*sht = (Elf64_Shdr *)((uint8_t *)ehdr + ehdr->e_shoff);
	char		c;

	if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE) {
		return 'u';
	} else if (sym->st_shndx == SHN_ABS) {
		return 'A';
	} else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK
		&& ELF64_ST_TYPE(sym->st_info) == STT_OBJECT) {
		if (sym->st_shndx == SHN_UNDEF)
			return 'v';
		return 'V';
	} else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
		if (sym->st_shndx == SHN_UNDEF)
			return 'w';
		return 'W';
	} else if (sym->st_shndx == SHN_UNDEF) {
		return 'U';
	} else if (sht[sym->st_shndx].sh_type == SHT_NOBITS
		&& sht[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) {
		c = 'B';
	} else if ((sht[sym->st_shndx].sh_type == SHT_PROGBITS
		&& sht[sym->st_shndx].sh_flags == SHF_ALLOC)
		|| sht[sym->st_shndx].sh_type == SHT_NOTE) {
		c = 'R';
	} else if ((sht[sym->st_shndx].sh_type == SHT_PROGBITS
			|| sht[sym->st_shndx].sh_type == SHT_PREINIT_ARRAY
			|| sht[sym->st_shndx].sh_type == SHT_INIT_ARRAY
			|| sht[sym->st_shndx].sh_type == SHT_FINI_ARRAY
			|| sht[sym->st_shndx].sh_type == SHT_DYNAMIC)
		&& sht[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) {
		c = 'D';
	} else if (sht[sym->st_shndx].sh_type == SHT_PROGBITS
		&& sht[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR)) {
		c = 'T';
	} else if (ELF64_ST_TYPE(sym->st_info) == STT_COMMON) {
		c = 'C';
	} else {
		return '?';
	}
	if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
		c += 32;
	return c;
	
}


//		which_type(ELF64_ST_TYPE(symtab[i]->st_info));
//		which_bind(ELF64_ST_BIND(symtab[i]->st_info));
//		which_other(ELF64_ST_VISIBILITY(symtab[i]->st_other));
//
void	which_shtype(int type)
{
	ft_printf(" %d ", type);
	if (type == SHT_NOBITS)
		ft_printf("SHT_NOBITS => ");
	if (type == SHT_PROGBITS)
		ft_printf("SHT_PROGBITS => ");
	if (type == SHT_HASH)
		ft_printf("SHT_HASH => ");
	if (type == SHT_RELA)
		ft_printf("SHT_RELA => ");
	if (type == SHT_REL)
		ft_printf("SHT_REL => ");
	if (type == SHT_SYMTAB)
		ft_printf("SHT_SYMTAB => ");
	if (type == SHT_STRTAB)
		ft_printf("SHT_STRTAB => ");
	if (type == SHT_PREINIT_ARRAY)
		ft_printf("SHT_PREINIT_ARRAY => ");
	if (type == SHT_INIT_ARRAY)
		ft_printf("SHT_INIT_ARRAY => ");
	if (type == SHT_FINI_ARRAY)
		ft_printf("SHT_FINI_ARRAY => ");
	if (type == SHT_DYNSYM)
		ft_printf("SHT_DYNSYM => ");
	if (type == SHT_DYNAMIC)
		ft_printf("SHT_DYNAMIC => ");

}


void	which_type(unsigned char type)
{
	if (type == STT_NOTYPE)
		ft_printf("NOTYPE => ");
	if (type == STT_SECTION)
		ft_printf("SECTION => ");
	if (type == STT_FILE)
		ft_printf("FILE => ");
	if (type == STT_FUNC)
		ft_printf("FUNC => ");
	if (type == STT_OBJECT)
		ft_printf("OBJECT => ");
}

void	which_bind(unsigned char bind)
{
	if (bind == STB_LOCAL)
		ft_printf("LOCAL => ");
	if (bind == STB_GLOBAL)
		ft_printf("GLOBAL => ");
	if (bind == STB_WEAK)
		ft_printf("WEAK => ");
}

void	which_other(unsigned char other)
{
	if (other == STV_DEFAULT)
		ft_printf("DEFAULT => ");
	if (other == STV_INTERNAL)
		ft_printf("INTERNAL => ");
	if (other == STV_HIDDEN)
		ft_printf("HIDDEN => ");
	if (other == STV_PROTECTED)
		ft_printf("PROTECTED => ");

}
