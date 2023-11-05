/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   print_symbols.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/05 02:37:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/05 22:35:45 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


void	which_type(unsigned char type);
void	which_bind(unsigned char bind);
void	which_other(unsigned char other);

char	print_letter64(Elf64_Sym *sym, Elf64_Ehdr *ehdr);


void	print_symbols(struct filedata_s *binary)
{
	
	Elf64_Sym	**symtab = (Elf64_Sym **)binary->symtab;
	
	for	(size_t i= 0; symtab[i]; i++) {
		if (symtab[i]->st_value)
			ft_printf("%016x", symtab[i]->st_value); 
		else
			ft_printf("                ");
		ft_printf(" %c ", print_letter64(symtab[i], (Elf64_Ehdr *)binary->file)); 
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
	} else if (sht[sym->st_shndx].sh_type == SHT_PROGBITS
		&& sht[sym->st_shndx].sh_flags == SHF_ALLOC) {
		c = 'R';
	} else if (sht[sym->st_shndx].sh_type == SHT_PROGBITS
		&& sht[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) {
		c = 'D';
	} else if (sht[sym->st_shndx].sh_type == SHT_PROGBITS
		&& sht[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR)) {
		c = 'T';
	} else if (sht[sym->st_shndx].sh_type == SHT_DYNAMIC) {
		c = 'D';
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
