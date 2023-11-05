/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   parse_class64.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/05 02:45:48 by amahla ###       ########     ########   */
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
	size_t	array_size = symsize / sizeof(Elf64_Sym);
	size_t	size = array_size;

	for (size_t i = 0; i < array_size; i++) {
		if (ELF64_ST_TYPE(symtab[i].st_info) == STT_FILE || symtab[i].st_name == '\00')
			size--;
	}
	binary->symtab = malloc(sizeof(Elf64_Sym *) * (size + 1));
	if (!binary->symtab) {
		ft_dprintf(2, "ft_nm: %s: \n", binary->name);
		perror(NULL);
		return FAILURE;
	}
	for (size_t i = 0, y = 0; i < array_size; i++) {
//		ft_printf("%s\n", strtab + symtab[i].st_name);
		if (ELF64_ST_TYPE(symtab[i].st_info) != STT_FILE && symtab[i].st_name != '\00')
			binary->symtab[y++] = symtab + i;
	}
	binary->symtab[size] = NULL;
	return SUCCESS;
}
