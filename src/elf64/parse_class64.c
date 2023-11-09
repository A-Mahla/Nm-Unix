/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   parse_class64.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/09 02:10:39 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


static bool	check_header(long int real_size, Elf64_Ehdr *ehdr);
static bool	check_symtab(Elf64_Shdr *sht, unsigned long int size);
static int	parse_symbol(Elf64_Ehdr *ehdr, struct filedata_s *binary, int ac);
static int	alloc_ptrsym(struct filedata_s *binary, size_t symsize, Elf64_Sym *symtab);


int	parse_class64(struct filedata_s *binary, int ac)
{
	Elf64_Ehdr	*header = (Elf64_Ehdr *)binary->file;

	if (!check_header(binary->size, header)) {
		err_parse(binary->name);
		return FAILURE;
	}
	if (parse_symbol(binary->file, binary, ac) == FAILURE && binary->strtab)
		return FAILURE;
	return SUCCESS;
}


static bool	check_header(long int binary_size, Elf64_Ehdr *ehdr)
{
	long int	size;

	size = ehdr->e_phoff + ehdr->e_phentsize * ehdr->e_phnum;
	if (binary_size < size)
		return false;
	size = ehdr->e_shoff + ehdr->e_shentsize * ehdr->e_shnum;
	if (binary_size != size)
		return false;
	return true;
}


static int	parse_symbol(Elf64_Ehdr *ehdr, struct filedata_s *binary, int ac)
{
	Elf64_Shdr	*sht = (Elf64_Shdr *)((uint8_t *)ehdr + ehdr->e_shoff);
	char		*shstrtab = (char *)((uint8_t *)ehdr + sht[ehdr->e_shstrndx].sh_offset);
	Elf64_Sym	*symtab = NULL;
	char		*strtab = NULL;
	size_t		symsize;

	for (int i = 0; i < ehdr->e_shnum; ++i) {
//		ft_printf("%s\n", shstrtab + sht[i].sh_name);
		if (i + 1 < ehdr->e_shnum && !check_symtab(sht + i, binary->size))
			goto err_no_symbols;
		if (ft_strncmp(shstrtab + sht[i].sh_name, ".symtab", ft_strlen(".symtab")) == 0) {
			symtab = (Elf64_Sym *)((uint8_t *)ehdr + sht[i].sh_offset);
			symsize = sht[i].sh_size;
		}
		if (ft_strncmp(shstrtab + sht[i].sh_name, ".strtab", ft_strlen(".strtab")) == 0)
			strtab = (char *)((uint8_t *)ehdr + sht[i].sh_offset);
	}
	binary->strtab = strtab;
	if (symtab == NULL || strtab == NULL)
		goto err_no_symbols;
	if (alloc_ptrsym(binary, symsize, symtab) == FAILURE)
		return FAILURE;
	return SUCCESS;
err_no_symbols:
	if (ac > 2)
		ft_dprintf(2, "\n%s:\n", binary->name);
	ft_dprintf(2, "nm: %s: no symbols\n", binary->name, binary->name);
	return FAILURE;
}


static bool	check_symtab(Elf64_Shdr *sht, unsigned long int size)
{
	if (sht[0].sh_offset + sht[0].sh_size > size) {
		if (sht[0].sh_offset == sht[1].sh_offset && sht[0].sh_offset < size)
			return true;
		return false;
	}
	return true;
}


static int	alloc_ptrsym(struct filedata_s *binary, size_t symsize, Elf64_Sym *symtab)
{
	size_t	array_size = symsize / sizeof(Elf64_Sym);
	size_t	size = array_size;

	for (size_t i = 0; i < array_size; i++) {
		if (ELF64_ST_TYPE(symtab[i].st_info) == STT_FILE || symtab[i].st_name == '\00')
			size--;
	}
	binary->symtab = malloc(sizeof(struct symtab_s) * (size + 1));
	if (!binary->symtab) {
		ft_dprintf(2, "nm: %s: \n", binary->name);
		perror(NULL);
		return FAILURE;
	}
	for (size_t i = 0, y = 0; i < array_size; i++) {
//		ft_printf("%s\n", strtab + symtab[i].st_name);
		if (ELF64_ST_TYPE(symtab[i].st_info) != STT_FILE && symtab[i].st_name != '\00') {
			binary->symtab[y].ptr = symtab + i;
			binary->symtab[y++].idx = i;
		}
	}
	binary->symtab[size].ptr = NULL;
	return SUCCESS;
}
