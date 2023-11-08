/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   nm.h                                            :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/29 21:09:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/08 17:00:27 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_H__
# define __NM_H__


# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <elf.h>
# include <stdint.h>
# include "libft.h"
# include "ft_printf.h"


# define SUCCESS 0
# define FAILURE -1
//# define EI_NIDENT 16 TO DELETE IF NOT USED
# define ELF_MAGIC_SIZE 4
# define ELF_MAGIC "\x7F\x45\x4C\x46"

struct symtab_s {
	void	*ptr;
	size_t	idx;
};

struct filedata_s {
	struct stat		statbuf;
	void			*file;
	struct symtab_s	*symtab;
	char			*strtab;
	char			*name;
	long int		size;
	uint8_t			ei_class;
};


int		open_file(struct filedata_s **binary, char *filename);
int		parse_file(struct filedata_s *binary, int ac);
int		parse_class32(struct filedata_s *binary, int ac);
int		parse_class64(struct filedata_s *binary, int ac);
void	print_symbols(struct filedata_s *binary);
char	find_letter64(Elf64_Sym *sym, Elf64_Ehdr *ehdr);
char	find_letter32(Elf32_Sym *sym, Elf32_Ehdr *ehdr);
void	quicksort64(char *strtab, struct symtab_s *symtab, size_t begin, size_t end);
void	quicksort32(char *strtab, struct symtab_s *symtab, size_t begin, size_t end);
int		ft_strcoll(char *str1, char *str2);
void	swap_sym(struct symtab_s *sym1, struct symtab_s *sym2);
void	err_parse(char *filename);

#endif
