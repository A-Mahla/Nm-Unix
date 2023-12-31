/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   parse_class32.c                                    :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/13 17:13:58 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


static bool	check_header(long int real_size, Elf32_Ehdr *ehdr, char *filename);
//static bool	check_symtab(Elf32_Shdr *sht, unsigned long int size);
static bool	check_symtab(Elf32_Shdr *sht, unsigned long int size, char *name);
static int	parse_symbol(Elf32_Ehdr *ehdr, struct filedata_s *binary, int ac);
static int	alloc_ptrsym(struct filedata_s *binary, size_t symsize, Elf32_Sym *symtab);


int	parse_class32(struct filedata_s *binary, int ac)
{
	Elf32_Ehdr	*header = (Elf32_Ehdr *)binary->file;

	if (!check_header(binary->size, header, binary->name)) {
		err_parse(binary->name);
		return FAILURE;
	}
	if (parse_symbol(binary->file, binary, ac) == FAILURE && binary->strtab)
		return FAILURE;
	return SUCCESS;
}


static bool	check_header(long int binary_size, Elf32_Ehdr *ehdr, char *filename)
{
	long int	size;

	size = ehdr->e_phoff + ehdr->e_phentsize * ehdr->e_phnum;
	if (binary_size < size)
		goto err_too_short;
	size = ehdr->e_shoff + ehdr->e_shentsize * ehdr->e_shnum;
	if (binary_size < size)
		goto err_too_short;
	return true;
err_too_short:
	ft_dprintf(2, "ft_nm: %s: file too short\n", filename);
	return false;
}


static int	parse_symbol(Elf32_Ehdr *ehdr, struct filedata_s *binary, int ac)
{
	Elf32_Shdr	*sht = (Elf32_Shdr *)((uint8_t *)ehdr + ehdr->e_shoff);
	char		*shstrtab = (char *)((uint8_t *)ehdr + sht[ehdr->e_shstrndx].sh_offset);
	Elf32_Sym	*symtab = NULL;
	char		*strtab = NULL;
	size_t		symsize;

	for (int i = 0; i < ehdr->e_shnum; ++i) {
//		ft_printf("%s\n", shstrtab + sht[i].sh_name);
		if (i + 1 < ehdr->e_shnum && !check_symtab(sht + i, binary->size, shstrtab + sht[i].sh_name))
			goto err_no_symbols;
		if (ft_strncmp(shstrtab + sht[i].sh_name, ".symtab", ft_strlen(".symtab")) == 0) {
			symtab = (Elf32_Sym *)((uint8_t *)ehdr + sht[i].sh_offset);
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


static bool	check_symtab(Elf32_Shdr *sht, unsigned long int size, char *name)
{
	if (sht[0].sh_offset + sht[0].sh_size > size
			&& ft_strnstr(name, "bss", ft_strlen("bss")) != 0) {
		if (sht[1].sh_offset < size)
			return true;
		return false;
	}
	return true;
}


static int	alloc_ptrsym(struct filedata_s *binary, size_t symsize, Elf32_Sym *symtab)
{
	size_t	array_size = symsize / sizeof(Elf32_Sym);
	size_t	size = array_size;

	for (size_t i = 0; i < array_size; i++) {
		if (ELF32_ST_TYPE(symtab[i].st_info) == STT_FILE || symtab[i].st_name == '\00')
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
		if (ELF32_ST_TYPE(symtab[i].st_info) != STT_FILE && symtab[i].st_name != '\00') {
			binary->symtab[y].ptr = symtab + i;
			binary->symtab[y++].idx = i;
		}
	}
	binary->symtab[size].ptr = NULL;
	return SUCCESS;
}
