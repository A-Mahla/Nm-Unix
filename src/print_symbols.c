/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   print_symbols.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/05 02:37:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/05 02:42:10 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


void	print_symbols(struct filedata_s *binary)
{
	for	(size_t i= 0; ((Elf64_Sym **)binary->symtab)[i]; i++) {
		ft_printf("%016x ", ((Elf64_Sym **)binary->symtab)[i]->st_value); 
		ft_printf("%s\n", binary->strtab + ((Elf64_Sym **)binary->symtab)[i]->st_name);
	}

}


//void	which_type(unsigned char type)
//{
//	if (type == STT_NOTYPE)
//		printf("NOTYPE => ");
//	if (type == STT_SECTION)
//		printf("SECTION => ");
//	if (type == STT_FILE)
//		printf("FILE => ");
//	if (type == STT_FUNC)
//		printf("FUNC => ");
//	if (type == STT_OBJECT)
//		printf("OBJECT => ");
//}
//
//void	which_bind(unsigned char bind)
//{
//	if (bind == STB_LOCAL)
//		printf("LOCAL => ");
//	if (bind == STB_GLOBAL)
//		printf("GLOBAL => ");
//	if (bind == STB_WEAK)
//		printf("WEAK => ");
//}
//
//void	which_other(unsigned char other)
//{
//	if (other == STV_DEFAULT)
//		printf("DEFAULT => ");
//	if (other == STV_INTERNAL)
//		printf("INTERNAL => ");
//	if (other == STV_HIDDEN)
//		printf("HIDDEN => ");
//	if (other == STV_PROTECTED)
//		printf("PROTECTED => ");
//
//}
