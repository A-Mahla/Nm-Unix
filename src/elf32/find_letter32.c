/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   find_letter32.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/05 02:37:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/12 20:19:40 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


static void	letter_u(unsigned char info, char *c);
static void	letter_A(unsigned char info, Elf32_Half shndx, char *c);
static void	letter_VWU(unsigned char info, Elf32_Half shndx, char *c);
static void	letter_B(Elf32_Word type, Elf32_Xword flags, char *c);
static void	letter_R(Elf32_Word type, Elf32_Xword flags, char *c);
static void	letter_D(Elf32_Word type, Elf32_Xword flags, char *c);
static void	letter_T(Elf32_Word type, Elf32_Xword flags, char *c);
static void	letter_C(unsigned char info, char *c);


char	find_letter32(Elf32_Sym *sym, Elf32_Ehdr *ehdr)
{
	Elf32_Shdr		*sht = (Elf32_Shdr *)((uint8_t *)ehdr + ehdr->e_shoff);
	Elf32_Half		shndx = sym->st_shndx;
	Elf32_Word		type;
	Elf32_Xword		flags;
	unsigned char	info = sym->st_info;
	char			c = '?';

	letter_C(info, &c);
	letter_u(info, &c);
	letter_A(info, shndx, &c);
	letter_VWU(info, shndx, &c);
	if (c != '?' || !sht)
		return c;
	type = sht[sym->st_shndx].sh_type;
	flags = sht[sym->st_shndx].sh_flags;
	letter_B(type, flags, &c);
	letter_R(type, flags, &c);
	letter_D(type, flags, &c);
	letter_T(type, flags, &c);
	if (ELF32_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
		c += 32;
	return c;
	
}


static void	letter_C(unsigned char info, char *c)
{
	if (ELF32_ST_TYPE(info) == STT_COMMON)
		*c = 'C';
}


static void	letter_u(unsigned char info, char *c)
{
	if (ELF32_ST_BIND(info) == STB_GNU_UNIQUE)
		*c = 'u';
}


static void	letter_A(unsigned char info, Elf32_Half shndx, char *c)
{
	if (shndx == SHN_ABS) {
		if (ELF32_ST_BIND(info) == STB_LOCAL)
			*c = 'a';
		else
			*c = 'A';
	}
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

// 'B/b' => sections : .bss / .tbss
static void	letter_B(Elf32_Word type, Elf32_Xword flags, char *c)
{
	if (type == SHT_NOBITS
		&& (flags == (SHF_ALLOC | SHF_WRITE)
			|| flags == (SHF_ALLOC | SHF_WRITE | SHF_TLS)))
		*c = 'B';
}


/* 'R/r' => sections : .rodata* / .dynamic / .dynstr /.dynsym /
 *						.hash / .note / .rela* / .SUNW_move / .SUNW_reloc / 
 *						.SUNW_syminfo / .SUNW_version
 */
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
		|| type == SHT_NOTE
		|| (type == SHT_PROGBITS && flags == (SHF_ALLOC | SHF_MERGE))
		|| (type == SHT_PROGBITS && flags == (SHF_ALLOC | SHF_MERGE | SHF_STRINGS)))
		*c = 'R';
}


// 'D/d' => sections : .data* / .init_array / .preinit_array / .fini_array
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


// 'T/t' => sections : .text / .plt
static void	letter_T(Elf32_Word type, Elf32_Xword flags, char *c)
{
	if ((type == SHT_PROGBITS && flags == (SHF_ALLOC | SHF_EXECINSTR))
		|| (type == SHT_PROGBITS
			&& flags == (SHF_ALLOC | SHF_EXECINSTR | SHF_GROUP))
		|| (type == SHT_PROGBITS
			&& flags == (SHF_ALLOC | SHF_WRITE | SHF_EXECINSTR)))
		*c = 'T';
}
