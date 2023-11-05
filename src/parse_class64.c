/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   parse_class64.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/05 02:40:41 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


bool	check_header64(long int real_size, Elf64_Ehdr *ehdr);
int		parse_symbol64(Elf64_Ehdr *ehdr, struct filedata_s *binary);
int		alloc_ptrsym64(struct filedata_s *binary, size_t symsize, Elf64_Sym *symtab);


int	parse_class64(struct filedata_s *binary)
{
	Elf64_Ehdr	*header = (Elf64_Ehdr *)binary->file;

	if (!check_header64(binary->size, header)) {
		err_parse(binary->name);
		return FAILURE;
	}
	if (parse_symbol64(binary->file, binary) == FAILURE)
		return FAILURE;
	return SUCCESS;
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
		if (sht[i].sh_offset + sht[i].sh_size > (unsigned long int)binary_size) {
			if (i + 1 < ehdr->e_shnum && sht[i].sh_offset == sht[i + 1].sh_offset 
					&& sht[i].sh_offset < (unsigned long int)binary_size)
				continue;
			return false;
		}
	}
	return true;
}


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
	if (symtab == NULL || strtab == NULL) {
		ft_dprintf(2, "ft_nm: %s: no symbols\n", binary->name);
		return FAILURE;
	}
	if (alloc_ptrsym64(binary, symsize, symtab) == FAILURE)
		return FAILURE;
	binary->strtab = strtab;
	sort(binary);
	return SUCCESS;
}


int	alloc_ptrsym64(struct filedata_s *binary, size_t symsize, Elf64_Sym *symtab)
{
	int size = symsize / sizeof(Elf64_Sym);

	for (size_t i = 0; i < symsize / sizeof(Elf64_Sym); i++) {
		if (ELF64_ST_TYPE(symtab[i].st_info) == STT_FILE || symtab[i].st_name == '\00')
			size--;
	}
	binary->symtab = malloc(sizeof(Elf64_Sym *) * (size + 1));
	if (!binary->symtab) {
		ft_dprintf(2, "ft_nm: %s: \n", binary->name);
		perror(NULL);
		return FAILURE;
	}
	for (size_t i = 0, y = 0; i < symsize / sizeof(Elf64_Sym); i++) {
//		ft_printf("%s\n", strtab + symtab[i].st_name);
		if (ELF64_ST_TYPE(symtab[i].st_info) != STT_FILE && symtab[i].st_name != '\00')
			binary->symtab[y++] = symtab + i;
	}
	binary->symtab[size] = NULL;
	return SUCCESS;
}


//void	sort64(struct filedata_s *binary)
//{
//	Elf64_Sym	**symtab64 = NULL;
//	Elf64_Sym	**symtab32 = NULL;
//	char		*strtab = binary->strtab;
//
//	if (binary->ei_class == ELFCLASS64) {
//		symtab64 = (Elf64_Sym **)binary->symtab;
//		for (size_t i = 0;  symtab64[i]; i++) {
//			for (size_t y = i + 1;  symtab64[y]; y++) {
//				if (ft_strcoll(strtab + symtab64[i]->st_name, strtab + symtab64[y]->st_name) > 0)
//					ft_swap_ptr((void *)(symtab64 + i), (void *)(symtab64 + y));
//			}
//		}
//	} else if (binary->ei_class == ELFCLASS32) {
//		symtab32 = (Elf32_Sym **)binary->symtab;
//		for (size_t i = 0;  symtab32[i]; i++) {
//			for (size_t y = i + 1;  symtab32[y]; y++) {
//				if (ft_strcoll(strtab + symtab32[i]->st_name, strtab + symtab32[y]->st_name) > 0)
//					ft_swap_ptr((void *)(symtab32 + i), (void *)(symtab32 + y));
//			}
//		}
//	}
//}
//
//
//int	ft_strcoll(char *str1, char *str2)
//{
//	char	c1, c2;
//	size_t	i = 0, y = 0;
//	int		f1 = 0, f2 = 0;
//	bool	upper1 = false, upper2 = false;
//
//	while (str1[i] && str1[i] == '_') {
//		f1++;
//		i++;
//	}
//	while (str2[y] && str2[y] == '_') {
//		f2++;
//		y++;
//	}
//	c1 = str1[i];
//	c2 = str2[y];
//	while (str1[i] && str2[y]) {
//		if (c1 >= 'A' && c1 <= 'Z' && c2 >= 'a' && c2 <= 'z') {
//			c1 += 32;
//			upper1 = true;
//		}
//		if (c2 >= 'A' && c2 <= 'Z' && c1 >= 'a' && c1 <= 'z') {
//			c2 += 32;
//			upper2 = true;
//		}
//		if (c1 != c2 )
//			break;
//		i++;
//		y++;
//		c1 = str1[i];
//		c2 = str2[y];
//	}
//	if (c1 == '\0' && c2 == '\0' && (f1 > f2 || (!upper1 && upper2)))
//		return -1;
//	if (c1 == '\0' && c2 == '\0' && (f1 < f2 || (upper1 && !upper2)))
//		return 1;
//	if (c1 == '@' && c2 != '@')
//		return 1;
//	if (c1 != '@' && c2 == '@')
//		return -1;
//	return c1 - c2;
//}
//
//
//void	ft_swap_ptr(void **ptr1, void **ptr2)
//{
//	void	*tmp;
//
//	tmp = *ptr1;
//	*ptr1 = *ptr2;
//	*ptr2 = tmp;
//}





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

