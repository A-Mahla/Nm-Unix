/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   parse_class32.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/01 02:08:24 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


int	parse_class32(struct filedata_s *binary)
{
	Elf32_Ehdr	*header = (Elf32_Ehdr *)binary->file;

	printf("%d\n", header->e_ehsize);


	ft_printf("Hi from class64 !\n");
	return SUCCESS;
//err:
//	err_parse(binary->name);
//	return FAILURE;
}
