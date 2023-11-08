/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   find_letter.c                                   :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/05 02:37:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/08 03:06:41 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


void	letter_u(unsigned char info, char *c);
void	letter_A(Elf64_Half shndx, char *c);
void	letter_VWU(unsigned char info, Elf64_Half shndx, char *c);
void	letter_B(Elf64_Word type, Elf64_Xword flags, char *c);
void	letter_R(Elf64_Word type, Elf64_Xword flags, char *c);
void	letter_D(Elf64_Word type, Elf64_Xword flags, char *c);
void	letter_T(Elf64_Word type, Elf64_Xword flags, char *c);
void	letter_C(unsigned char info, char *c);


char	find_letter64(Elf64_Sym *sym, Elf64_Ehdr *ehdr)
{
	Elf64_Shdr		*sht = (Elf64_Shdr *)((uint8_t *)ehdr + ehdr->e_shoff);
	Elf64_Word		type = sht[sym->st_shndx].sh_type;
	Elf64_Xword		flags = sht[sym->st_shndx].sh_flags;
	Elf64_Half		shndx = sym->st_shndx;
	unsigned char	info = sym->st_info;
	char			c = '?';

	letter_u(info, &c);
	letter_A(shndx, &c);
	letter_VWU(info, shndx, &c);
	if (c != '?')
		return c;
	letter_B(type, flags, &c);
	letter_R(type, flags, &c);
	letter_D(type, flags, &c);
	letter_T(type, flags, &c);
	letter_C(info, &c);
	if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
		c += 32;
	return c;
	
}


char	find_letter32(Elf32_Sym *sym, Elf32_Ehdr *ehdr)
{
	Elf32_Shdr		*sht = (Elf32_Shdr *)((uint8_t *)ehdr + ehdr->e_shoff);
	Elf32_Word		type = sht[sym->st_shndx].sh_type;
	Elf32_Xword		flags = sht[sym->st_shndx].sh_flags;
	Elf32_Half		shndx = sym->st_shndx;
	unsigned char	info = sym->st_info;
	char			c = '?';

	letter_u(info, &c);
	letter_A(shndx, &c);
	letter_VWU(info, shndx, &c);
	if (c != '?')
		return c;
	letter_B(type, flags, &c);
	letter_R(type, flags, &c);
	letter_D(type, flags, &c);
	letter_T(type, flags, &c);
	letter_C(info, &c);
	if (ELF32_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
		c += 32;
	return c;
	
}


void	letter_u(unsigned char info, char *c)
{
	if (ELF64_ST_BIND(info) == STB_GNU_UNIQUE)
		*c = 'u';
}


void	letter_A(Elf64_Half shndx, char *c)
{
	if (shndx == SHN_ABS)
		*c = 'A';
}


void	letter_VWU(unsigned char info, Elf64_Half shndx, char *c)
{
	if (ELF64_ST_BIND(info) == STB_WEAK
		&& ELF64_ST_TYPE(info) == STT_OBJECT) {
		if (shndx == SHN_UNDEF)
			*c = 'v';
		else
			*c = 'V';
	} else if (ELF64_ST_BIND(info) == STB_WEAK) {
		if (shndx == SHN_UNDEF)
			*c = 'w';
		else
			*c = 'W';
	} else if (shndx == SHN_UNDEF) {
		*c = 'U';
	}
}


void	letter_B(Elf64_Word type, Elf64_Xword flags, char *c)
{
	if (type == SHT_NOBITS
		&& (flags == (SHF_ALLOC | SHF_WRITE)
			|| flags == (SHF_ALLOC | SHF_WRITE | SHF_TLS)))
		*c = 'B';
}


void	letter_R(Elf64_Word type, Elf64_Xword flags, char *c)
{
	if (((type == SHT_PROGBITS
				|| type == SHT_RELA
				|| type == SHT_REL
				|| type == SHT_HASH
				|| type == SHT_STRTAB
				|| type == SHT_DYNSYM
				|| type == SHT_SUNW_move
				|| type == SHT_SUNW_syminfo
				|| type == SHT_GNU_verdef
				|| type == SHT_GNU_verneed
				|| type == SHT_GNU_versym)
			&& flags == SHF_ALLOC)
		|| type == SHT_NOTE)
		*c = 'R';
}


void	letter_D(Elf64_Word type, Elf64_Xword flags, char *c)
{
	if (((type == SHT_PROGBITS
				|| type == SHT_PREINIT_ARRAY
				|| type == SHT_INIT_ARRAY
				|| type == SHT_FINI_ARRAY
				|| type == SHT_DYNAMIC)
			&& flags == (SHF_ALLOC | SHF_WRITE))
		|| (type == SHT_PROGBITS
			&& flags == (SHF_ALLOC | SHF_WRITE | SHF_TLS)))
		*c = 'D';
}


void	letter_T(Elf64_Word type, Elf64_Xword flags, char *c)
{
	if (type == SHT_PROGBITS
		&& flags == (SHF_ALLOC | SHF_EXECINSTR))
		*c = 'T';
}


void	letter_C(unsigned char info, char *c)
{
	if (ELF64_ST_TYPE(info) == STT_COMMON)
		*c = 'C';
}
