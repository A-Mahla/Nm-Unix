/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   nm.h                                            :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/29 21:09:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/01 01:55:42 by amahla ###       ########     ########   */
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


struct filedata_s {
	struct stat	statbuf;
	void		*file;
	char		*name;
	long long int	size;
	uint8_t		ei_class;
};


int		open_file(struct filedata_s **binary, char *filename);
int		parse_file(int ac, struct filedata_s *binary);
int		parse_class32(struct filedata_s *binary);
int		parse_class64(struct filedata_s *binary);
void	err_parse(char *filename);


#endif
