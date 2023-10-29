/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   nm.h                                            :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/29 21:09:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/30 00:24:29 by amahla ###       ########     ########   */
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
# include <stdint.h>
# include "libft.h"
# include "ft_printf.h"


# define SUCCESS 0
# define FAILURE -1



struct filedata_s {
	struct stat	statbuf;
	uint8_t		*file;
};


int		open_file(struct filedata_s **binary, char *filename);
void	exit_free(struct filedata_s	*binary);


#endif
