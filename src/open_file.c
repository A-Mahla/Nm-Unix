/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   open_file.c                                     :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/29 21:33:41 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/30 23:23:33 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


void	err_file(char *filename);
int		read_file(int fd, struct filedata_s *binary);


int	open_file(struct filedata_s **binary, char *filename)
{
	int	fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		goto err;
	if ((*binary = malloc(sizeof(struct filedata_s))) == NULL)
		goto err;
	(*binary)->file = NULL;
	(*binary)->name = filename;
	if (read_file(fd, *binary) == FAILURE)
		goto err;
	close(fd);
	return SUCCESS;
err:
	err_file(filename);
	return FAILURE;
}


int	read_file(int fd, struct filedata_s *binary)
{
	int rd;

	if (fstat(fd, &binary->statbuf) < 0)
		goto err;
	if ((binary->file = malloc(binary->statbuf.st_size + 1)) == NULL)
		goto err;
	if ((rd = read(fd, binary->file, binary->statbuf.st_size)) < 0)
		goto err;
//	binary->file[rd] = '\0'; TO DELETE IF NOT USED
	binary->size = rd;
	return SUCCESS;
err:
	return FAILURE;
}


void	err_file(char *filename)
{
	ft_dprintf(2, "ft_nm: '%s': ", filename);
	perror(NULL);
}
