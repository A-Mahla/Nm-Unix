/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   sort.c                                          :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 00:19:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/05 00:53:16 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"



void	sort(struct filedata_s *binary);
void	swap_ptr(void **ptr1, void **ptr2);
int		ft_strcoll(char *str1, char *str2);
void	underscore_counter(char **str, size_t *count);
void	tolower_coll(char *c1, char c2, bool *upper);


void	sort(struct filedata_s *binary)
{
	Elf64_Sym	**symtab64 = NULL;
	Elf32_Sym	**symtab32 = NULL;
	char		*strtab = binary->strtab;

	if (binary->ei_class == ELFCLASS64) {
		symtab64 = (Elf64_Sym **)binary->symtab;
		for (size_t i = 0;  symtab64[i]; i++) {
			for (size_t y = i + 1;  symtab64[y]; y++) {
				if (ft_strcoll(strtab + symtab64[i]->st_name, strtab + symtab64[y]->st_name) > 0)
					swap_ptr((void *)(symtab64 + i), (void *)(symtab64 + y));
			}
		}
	} else if (binary->ei_class == ELFCLASS32) {
		symtab32 = (Elf32_Sym **)binary->symtab;
		for (size_t i = 0;  symtab32[i]; i++) {
			for (size_t y = i + 1;  symtab32[y]; y++) {
				if (ft_strcoll(strtab + symtab32[i]->st_name, strtab + symtab32[y]->st_name) > 0)
					swap_ptr((void *)(symtab32 + i), (void *)(symtab32 + y));
			}
		}
	}
}


int	ft_strcoll(char *str1, char *str2)
{
	char	c1, c2;
	size_t	i = 0, y = 0;
	size_t	f1 = 0, f2 = 0;
	bool	upper1 = false, upper2 = false;

	underscore_counter(&str1, &f1);
	underscore_counter(&str2, &f2);
	c1 = str1[i];
	c2 = str2[y];
	while (str1[i++] && str2[y++]) {
		tolower_coll(&c1, c2, &upper1);
		tolower_coll(&c2, c1, &upper2);
		if (c1 != c2 )
			break;
		c1 = str1[i];
		c2 = str2[y];
	}
	if (c1 == '\0' && c2 == '\0' && (f1 < f2 || (upper1 && !upper2)))
		return 1;
	if (c1 == '\0' && c2 == '\0' && (f1 > f2 || (!upper1 && upper2)))
		return -1;
	if (c1 == '@' && c2 != '@')
		return 1;
	if (c1 != '@' && c2 == '@')
		return -1;
	return c1 - c2;
}


void	underscore_counter(char **str, size_t *count)
{
	while (**str && **str == '_') {
		(*count)++;
		(*str)++;
	}
}


void	tolower_coll(char *c1, char c2, bool *upper)
{
	if (*c1 >= 'A' && *c1 <= 'Z' && c2 >= 'a' && c2 <= 'z') {
		*c1 += 32;
		*upper = true;
	}
}


void	swap_ptr(void **ptr1, void **ptr2)
{
	void	*tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}
