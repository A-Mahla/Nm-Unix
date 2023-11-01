/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   file_parser.c                                   :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/30 22:34:49 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/01 01:57:49 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


bool	check_size(struct filedata_s *binary);
void	err_parse(char *filename);


int	parse_file(int ac, struct filedata_s *binary)
{
// To Delete if I have a checker on each symbol for oversize binary->size
	if (!check_size(binary))
		goto err;
//////////////////////////////////////////////
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


void	err_parse(char *filename)
{
	ft_dprintf(2, "ft_nm: '%s': file too short\n", filename);
	ft_dprintf(2, "ft_nm: '%s': file format not recognized\n", filename);
}


// To Delete if I have a checker on each symbol for oversize binary->size
bool	check_size(struct filedata_s *binary)
{
	if (binary->statbuf.st_size != binary->size) {
		ft_dprintf(2, "ft_nm: '%s': Fatal Error\n", binary->name);
		return false;
	}
	return true;
}
//
