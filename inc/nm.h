/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   nm.h                                            :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/29 21:09:19 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/29 22:23:11 by amahla ###       ########     ########   */
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
# include "libft.h"
# include "ft_printf.h"


struct filedata_s {
	struct stat	*statbuf;
	char		*file;
};


struct filedata_s	*open_file(char *filename);


#endif
