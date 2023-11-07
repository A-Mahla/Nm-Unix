/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   file_parser.c                                   :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/30 22:34:49 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/08 00:45:57 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


void	sort(struct filedata_s *binary);
size_t	size_symtab(struct symtab_s *symtab);
bool	check_fatal_error(struct filedata_s *binary);
void	err_parse(char *filename);


int	parse_file(struct filedata_s *binary, int ac)
{
	if (!check_fatal_error(binary))
		goto err;
	if (binary->ei_class == ELFCLASS32) {
		if (parse_class32(binary) == FAILURE)
			goto err;
	} else {
		if (parse_class64(binary, ac) == FAILURE)
			goto err;
	}
	sort(binary);
	return SUCCESS;
err:
	return FAILURE;
}


void	sort(struct filedata_s *binary)
{
	struct symtab_s	*symtab = (struct symtab_s *)binary->symtab;
	char		*strtab = binary->strtab;

	if (binary->ei_class == ELFCLASS64)
		quicksort64(strtab, symtab, 0, size_symtab(symtab) - 1);
	else if (binary->ei_class == ELFCLASS32)
		quicksort64(strtab, symtab, 0, size_symtab(symtab) - 1);
}


size_t	size_symtab(struct symtab_s *symtab)
{
	size_t	count = 0;

	while(symtab[count].ptr)
		count++;
	return count;
}


void	err_parse(char *filename)
{
//	ft_dprintf(2, "ft_nm: '%s': file too short\n", filename);
	ft_dprintf(2, "nm: %s: file format not recognized\n", filename);
}


bool	check_fatal_error(struct filedata_s *binary)
{
	if (binary->statbuf.st_size != binary->size) {
		ft_dprintf(2, "ft_nm: %s: Fatal Error\n", binary->name);
		return false;
	}
	return true;
}
