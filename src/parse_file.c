/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   parse_file.c                                    :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/30 22:34:49 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/31 00:41:55 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"

//bfd plugin: test: file too short
//nm: test: file format not recognized
bool	check_size(struct filedata_s *binary);
bool	check_magic(struct filedata_s *binary);


int	parse_file(int ac, struct filedata_s *binary)
{
	if (!check_size(binary))
		goto err;
	if (!check_magic(binary))
		goto err;
	if (binary->ei_class == ELFCLASS32) {
		if (parse_class32(binary) == FAILURE)
			goto err;
	} else {
		if (parse_class64(binary) == FAILURE)
			goto err;
	}
	if (ac > 2)
		ft_printf("\n%s:\n", binary->name);
	return SUCCESS;
err:
	return FAILURE;
}


bool	check_size(struct filedata_s *binary)
{
	if (binary->statbuf.st_size == 0) {
		return false;
	} else if (binary->statbuf.st_size != binary->size) {
		ft_dprintf(2, "ft_nm: '%s': Fatal Error\n", binary->name);
		return false;
	} else if (binary->statbuf.st_size < 64) {
		ft_dprintf(2, "ft_nm: '%s': file format not recognized\n", binary->name);
		return false;
	}
	return true;
}


bool	check_magic(struct filedata_s *binary)
{
	unsigned char	*e_indent;

	e_indent = (unsigned char *)binary->file;
	if (ft_memcmp(e_indent, ELF_MAGIC, ELF_MAGIC_SIZE) != 0)
		goto err;
	if (e_indent[EI_CLASS] != ELFCLASS32 && e_indent[EI_CLASS] != ELFCLASS64)
		goto err;
	binary->ei_class = e_indent[EI_CLASS];
	return true;
err:
	ft_dprintf(2, "ft_nm: '%s': file format not recognized\n", binary->name);
	return false;
}
