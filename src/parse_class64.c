/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   parse_class64.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/02 15:48:05 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


bool	check_header64(long int real_size, Elf64_Ehdr *ehdr);


int	parse_class64(struct filedata_s *binary)
{
	Elf64_Ehdr	*header = (Elf64_Ehdr *)binary->file;

	if (!check_header64(binary->size, header))
		goto err;
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
