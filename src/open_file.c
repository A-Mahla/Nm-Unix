/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   open_file.c                                     :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/29 21:33:41 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/29 22:46:28 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


struct filedata_s	*read_file(int fd)
{
	struct filedata_s	*binary;

	if ((binary = malloc(sizeof(struct filedata_s *))) == NULL) {
		ft_printf("");
		perror("");
		return NULL;
	}
	(void)fd;

//	fstat(int fd, struct stat *statbuf);
	return NULL;
}


struct filedata_s	*open_file(char *filename)
{
	int	fd;

	if ((fd = open(filename, O_RDONLY)) < 0) {
		ft_dprintf(2, "ft_nm: '%s': ", filename);
		perror(NULL);
		exit(1);
	}
	
	
	return NULL;
}
