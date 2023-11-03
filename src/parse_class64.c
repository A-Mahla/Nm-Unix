/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   parse_class64.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/03 15:34:33 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


bool	check_header64(long int real_size, Elf64_Ehdr *ehdr);
int		parse_symbol64(Elf64_Ehdr *ehdr, struct filedata_s *binary);
int		alloc_ptrsym64(struct filedata_s *binary, size_t size);


int	parse_class64(struct filedata_s *binary)
{
	Elf64_Ehdr	*header = (Elf64_Ehdr *)binary->file;

	if (!check_header64(binary->size, header))
		goto err;
	parse_symbol64(binary->file, binary);
//	ft_printf("Hi from class64 !\n");
	return SUCCESS;
err:
	err_parse(binary->name);
	return FAILURE;
}


bool	check_header64(long int binary_size, Elf64_Ehdr *ehdr)
{
	Elf64_Shdr	*sht = (Elf64_Shdr *) ((uint8_t *)ehdr + ehdr->e_shoff);
	long int	size;

	size = ehdr->e_phoff + ehdr->e_phentsize * ehdr->e_phnum;
	if (binary_size < size)
		return false;
	size = ehdr->e_shoff + ehdr->e_shentsize * ehdr->e_shnum;
	if (binary_size != size)
		return false;
	for (int i = 1; i < ehdr->e_shnum; i++) {
		if (sht[i].sh_offset + sht[i].sh_size > (unsigned long int)binary_size)
			return false;
	}
	return true;
}





void	which_bind(unsigned char bind);
void	which_type(unsigned char type);
void	which_other(unsigned char other);


int	parse_symbol64(Elf64_Ehdr *ehdr, struct filedata_s *binary)
{
	Elf64_Shdr	*sht = (Elf64_Shdr *)((uint8_t *)ehdr + ehdr->e_shoff);
	char		*shstrtab = (char *)((uint8_t *)ehdr + sht[ehdr->e_shstrndx].sh_offset);
	Elf64_Sym	*symtab = NULL;
	char		*strtab = NULL;
	size_t		symsize;

	for (int i = 0; i < ehdr->e_shnum; ++i) {
//		ft_printf("%s\n", shstrtab + sht[i].sh_name);
		if (ft_strncmp(shstrtab + sht[i].sh_name, ".symtab", ft_strlen(".symtab")) == 0) {
			symtab = (Elf64_Sym *)((uint8_t *)ehdr + sht[i].sh_offset);
			symsize = sht[i].sh_size;
		}
		if (ft_strncmp(shstrtab + sht[i].sh_name, ".strtab", ft_strlen(".strtab")) == 0)
			strtab = (char *)((uint8_t *)ehdr + sht[i].sh_offset);
	}
	if (symtab == NULL || strtab == NULL
			|| alloc_ptrsym64(binary, symsize / sizeof(Elf64_Sym)) == FAILURE)
		return FAILURE;
	binary->strtab = strtab;
	for	(size_t i = 0; i < symsize / sizeof(Elf64_Sym); i++) {
//		ft_printf("%s\n", strtab + symtab[i].st_name);
		binary->symtab[i] = symtab + i;
	}
	for	(size_t i = 0; i < symsize / sizeof(Elf64_Sym); i++)
		ft_printf("%s\n", binary->strtab + ((Elf64_Sym **)binary->symtab)[i]->st_name);
	return SUCCESS;
}


int	alloc_ptrsym64(struct filedata_s *binary, size_t size)
{
	binary->symtab = malloc(sizeof(Elf64_Sym *) * (size + 1));
	if (!binary->symtab)
		return FAILURE;
	binary->symtab[size] = NULL;
	return SUCCESS;
}



















//void parseSymbols (uint8_t *map)
//{
//	Elf64_Ehdr *ehdr = (Elf64_Ehdr *) map;
//	Elf64_Shdr *sht  = (Elf64_Shdr *) &map[ehdr->e_shoff];
//	char *shstrtab   = (char *) &map[sht[ehdr->e_shstrndx].sh_offset];
//	Elf64_Sym *symtab = NULL, *dynsym = NULL;
//	uint64_t dynsym_size = 0, symtab_size = 0;
//	char *dynstr = NULL, *strtab = NULL;
//
//
//	for (int i = 0; i < ehdr->e_shnum; ++i) {
//		char *section_name = &shstrtab[sht[i].sh_name];
//
//		/* dynamic symbols found */
//		if (strncmp (".dynsym", section_name, strlen(".dynsym")) == 0 &&
//			sht[i].sh_type == SHT_DYNSYM) {
////			fprintf (stderr, "%s shdr @ 0x%lx\n", section_name, sht[i].sh_offset);
//			dynsym = (Elf64_Sym *) &map[sht[i].sh_offset];
//			dynsym_size = sht[i].sh_size;
//		}
//
//		/* .dynstr section found */
//		if (strncmp (".dynstr", section_name, strlen(".dynstr")) == 0 &&
//			sht[i].sh_type == SHT_STRTAB) {
////			fprintf (stderr, "%s shdr @ 0x%lx\n", section_name, sht[i].sh_offset);
//			dynstr = (char *) &map[sht[i].sh_offset];
//		}
//
//
//		/* static symbols found */
//		if (strncmp (".symtab", section_name, strlen (".symtab")) == 0 &&
//			sht[i].sh_type == SHT_SYMTAB) {
////			fprintf (stderr, "%s shdr @ 0x%lx\n", section_name, sht[i].sh_offset);
//			symtab = (Elf64_Sym *) &map[sht[i].sh_offset];
//			symtab_size = sht[i].sh_size;
//		}
//
//		/* .strtab section found */
//		if (strncmp (".strtab", section_name, strlen (".strtab")) == 0 &&
//			sht[i].sh_type == SHT_STRTAB) {
////			fprintf (stderr, "%s shdr @ 0x%lx\n", section_name, sht[i].sh_offset);
//			strtab = (char *) &map[sht[i].sh_offset];
//		}
//	}
//
//	/* parsing dynamic symbol table */
////	fprintf (stderr, "\n\n# .dynsym entries: \n");
//	for (uint64_t i = 0; i < dynsym_size / sizeof (Elf64_Sym); ++i) {
//		char *symname = &dynstr[dynsym[i].st_name];
//
////		fprintf (stdout, "\t0x%06lx: ", dynsym[i].st_value);
////		if (ELF64_ST_TYPE(symtab[i].st_info) == STT_FILE)
////			continue;
////		if (ELF64_ST_TYPE(symtab[i].st_info) == STT_SECTION)
////			continue;
////		if (ELF64_ST_TYPE(symtab[i].st_info) == STT_FUNC && ELF64_ST_BIND(symtab[i].st_info) == STB_LOCAL
////			&& ELF64_ST_VISIBILITY(symtab[i].st_other) == STV_DEFAULT)
////			continue;
////		which_type(ELF64_ST_TYPE(symtab[i].st_info));
////		which_bind(ELF64_ST_BIND(symtab[i].st_info));
////		which_other(ELF64_ST_VISIBILITY(symtab[i].st_other));
//		if (*symname == '\x00')
//			continue;
////			fprintf (stdout, "NULL\n");
//		else
//			continue;
////			fprintf (stdout, "%s\n", symname);
//	}
//
//	/* parsing static symbol table */
////	fprintf (stdout, "\n# .symtab entries: \n");
//	for (uint64_t i = 0; i < symtab_size / sizeof (Elf64_Sym); ++i) {
//		if (ELF64_ST_TYPE(symtab[i].st_info) == STT_FILE)
//			continue;
////		if (ELF64_ST_TYPE(symtab[i].st_info) == STT_SECTION)
////			continue;
////		if (ELF64_ST_TYPE(symtab[i].st_info) == STT_FUNC && ELF64_ST_BIND(symtab[i].st_info) == STB_LOCAL
////			&& ELF64_ST_VISIBILITY(symtab[i].st_other) == STV_DEFAULT)
////			continue;
////		which_type(ELF64_ST_TYPE(symtab[i].st_info));
////		which_bind(ELF64_ST_BIND(symtab[i].st_info));
////		which_other(ELF64_ST_VISIBILITY(symtab[i].st_other));
//		char *symname = &strtab[symtab[i].st_name];
////		fprintf (stdout, "\t0x%06lx: ", symtab[i].st_value);
//		if (*symname == '\x00')
//			continue;
//		else
//			fprintf (stdout, "%s\n", symname);
//	}
//}

void	which_type(unsigned char type)
{
	if (type == STT_NOTYPE)
		printf("NOTYPE => ");
	if (type == STT_SECTION)
		printf("SECTION => ");
	if (type == STT_FILE)
		printf("FILE => ");
	if (type == STT_FUNC)
		printf("FUNC => ");
	if (type == STT_OBJECT)
		printf("OBJECT => ");
}

void	which_bind(unsigned char bind)
{
	if (bind == STB_LOCAL)
		printf("LOCAL => ");
	if (bind == STB_GLOBAL)
		printf("GLOBAL => ");
	if (bind == STB_WEAK)
		printf("WEAK => ");
}

void	which_other(unsigned char other)
{
	if (other == STV_DEFAULT)
		printf("DEFAULT => ");
	if (other == STV_INTERNAL)
		printf("INTERNAL => ");
	if (other == STV_HIDDEN)
		printf("HIDDEN => ");
	if (other == STV_PROTECTED)
		printf("PROTECTED => ");

}
