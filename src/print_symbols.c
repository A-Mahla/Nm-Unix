/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   print_symbols.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/05 02:37:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/05 03:07:43 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


void	which_type(unsigned char type);
void	which_bind(unsigned char bind);
void	which_other(unsigned char other);


void	print_symbols(struct filedata_s *binary)
{
	Elf64_Sym	**symtab = (Elf64_Sym **)binary->symtab;
	
	for	(size_t i= 0; symtab[i]; i++) {
		ft_printf("%016x ", symtab[i]->st_value); 
		ft_printf("%s\n", binary->strtab + symtab[i]->st_name);
	}

}


//		which_type(ELF64_ST_TYPE(symtab[i]->st_info));
//		which_bind(ELF64_ST_BIND(symtab[i]->st_info));
//		which_other(ELF64_ST_VISIBILITY(symtab[i]->st_other));

void	which_type(unsigned char type)
{
	if (type == STT_NOTYPE)
		ft_printf("NOTYPE => ");
	if (type == STT_SECTION)
		ft_printf("SECTION => ");
	if (type == STT_FILE)
		ft_printf("FILE => ");
	if (type == STT_FUNC)
		ft_printf("FUNC => ");
	if (type == STT_OBJECT)
		ft_printf("OBJECT => ");
}

void	which_bind(unsigned char bind)
{
	if (bind == STB_LOCAL)
		ft_printf("LOCAL => ");
	if (bind == STB_GLOBAL)
		ft_printf("GLOBAL => ");
	if (bind == STB_WEAK)
		ft_printf("WEAK => ");
}

void	which_other(unsigned char other)
{
	if (other == STV_DEFAULT)
		ft_printf("DEFAULT => ");
	if (other == STV_INTERNAL)
		ft_printf("INTERNAL => ");
	if (other == STV_HIDDEN)
		ft_printf("HIDDEN => ");
	if (other == STV_PROTECTED)
		ft_printf("PROTECTED => ");

}
