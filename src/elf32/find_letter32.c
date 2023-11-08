/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   find_letter64.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/05 02:37:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/08 15:15:59 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


static void	letter_u(unsigned char info, char *c);
static void	letter_A(Elf32_Half shndx, char *c);
static void	letter_VWU(unsigned char info, Elf32_Half shndx, char *c);
static void	letter_B(Elf32_Word type, Elf32_Xword flags, char *c);
static void	letter_R(Elf32_Word type, Elf32_Xword flags, char *c);
static void	letter_D(Elf32_Word type, Elf32_Xword flags, char *c);
static void	letter_T(Elf32_Word type, Elf32_Xword flags, char *c);
static void	letter_C(unsigned char info, char *c);


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


static void	letter_u(unsigned char info, char *c)
{
	if (ELF32_ST_BIND(info) == STB_GNU_UNIQUE)
		*c = 'u';
}


static void	letter_A(Elf32_Half shndx, char *c)
{
	if (shndx == SHN_ABS)
		*c = 'A';
}


static void	letter_VWU(unsigned char info, Elf32_Half shndx, char *c)
{
	if (ELF32_ST_BIND(info) == STB_WEAK
		&& ELF32_ST_TYPE(info) == STT_OBJECT) {
		if (shndx == SHN_UNDEF)
			*c = 'v';
		else
			*c = 'V';
	} else if (ELF32_ST_BIND(info) == STB_WEAK) {
		if (shndx == SHN_UNDEF)
			*c = 'w';
		else
			*c = 'W';
	} else if (shndx == SHN_UNDEF) {
		*c = 'U';
	}
}


static void	letter_B(Elf32_Word type, Elf32_Xword flags, char *c)
{
	if (type == SHT_NOBITS
		&& (flags == (SHF_ALLOC | SHF_WRITE)
			|| flags == (SHF_ALLOC | SHF_WRITE | SHF_TLS)))
		*c = 'B';
}


static void	letter_R(Elf32_Word type, Elf32_Xword flags, char *c)
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


static void	letter_D(Elf32_Word type, Elf32_Xword flags, char *c)
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


static void	letter_T(Elf32_Word type, Elf32_Xword flags, char *c)
{
	if (type == SHT_PROGBITS
		&& flags == (SHF_ALLOC | SHF_EXECINSTR))
		*c = 'T';
}


static void	letter_C(unsigned char info, char *c)
{
	if (ELF32_ST_TYPE(info) == STT_COMMON)
		*c = 'C';
}