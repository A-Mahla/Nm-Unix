/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   parse_class64.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/02 16:30:20 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


bool	check_header64(long int real_size, Elf64_Ehdr *ehdr);
void	parseSymbols(uint8_t *map);


int	parse_class64(struct filedata_s *binary)
{
	Elf64_Ehdr	*header = (Elf64_Ehdr *)binary->file;

	if (!check_header64(binary->size, header))
		goto err;
	parseSymbols(binary->file);
	ft_printf("Hi from class64 !\n");
	return SUCCESS;
err:
	err_parse(binary->name);
	return FAILURE;
}


bool	check_header64(long int binary_size, Elf64_Ehdr *ehdr)
{
	Elf64_Shdr *sht;
	long int	size;

	sht = (Elf64_Shdr *) ((uint8_t *)ehdr + ehdr->e_shoff);
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


void parseSymbols (uint8_t *map) {
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *) map;
	Elf64_Shdr *sht  = (Elf64_Shdr *) &map[ehdr->e_shoff];
	char *shstrtab   = (char *) &map[sht[ehdr->e_shstrndx].sh_offset];
	Elf64_Sym *symtab = NULL, *dynsym = NULL;
	uint64_t dynsym_size = 0, symtab_size = 0;
	char *dynstr = NULL, *strtab = NULL;


	for (int i = 0; i < ehdr->e_shnum; ++i) {
		char *section_name = &shstrtab[sht[i].sh_name];

		/* dynamic symbols found */
		if (strncmp (".dynsym", section_name, strlen(".dynsym")) == 0 &&
			sht[i].sh_type == SHT_DYNSYM) {
			fprintf (stderr, "%s shdr @ 0x%lx\n", section_name, sht[i].sh_offset);
			dynsym = (Elf64_Sym *) &map[sht[i].sh_offset];
			dynsym_size = sht[i].sh_size;
		}

		/* .dynstr section found */
		if (strncmp (".dynstr", section_name, strlen(".dynstr")) == 0 &&
			sht[i].sh_type == SHT_STRTAB) {
			fprintf (stderr, "%s shdr @ 0x%lx\n", section_name, sht[i].sh_offset);
			dynstr = (char *) &map[sht[i].sh_offset];
		}


		/* static symbols found */
		if (strncmp (".symtab", section_name, strlen (".symtab")) == 0 &&
			sht[i].sh_type == SHT_SYMTAB) {
			fprintf (stderr, "%s shdr @ 0x%lx\n", section_name, sht[i].sh_offset);
			symtab = (Elf64_Sym *) &map[sht[i].sh_offset];
			symtab_size = sht[i].sh_size;
		}

		/* .strtab section found */
		if (strncmp (".strtab", section_name, strlen (".strtab")) == 0 &&
			sht[i].sh_type == SHT_STRTAB) {
			fprintf (stderr, "%s shdr @ 0x%lx\n", section_name, sht[i].sh_offset);
			strtab = (char *) &map[sht[i].sh_offset];
		}
	}

	/* parsing dynamic symbol table */
	fprintf (stderr, "\n\n# .dynsym entries: \n");
	for (uint64_t i = 0; i < dynsym_size / sizeof (Elf64_Sym); ++i) {
		char *symname = &dynstr[dynsym[i].st_name];

		fprintf (stderr, "\t0x%06lx: ", dynsym[i].st_value);
		if (*symname == '\x00')
			fprintf (stderr, "NULL\n");
		else
			fprintf (stderr, "%s\n", symname);
	}

	/* parsing static symbol table */
	fprintf (stderr, "\n# .symtab entries: \n");
	for (uint64_t i = 0; i < symtab_size / sizeof (Elf64_Sym); ++i) {
		char *symname = &strtab[symtab[i].st_name];
		fprintf (stderr, "\t0x%06lx: ", symtab[i].st_value);
		if (*symname == '\x00')
			fprintf (stderr, "NULL\n");
		else
			fprintf (stderr, "%s\n", symname);
	}
}
