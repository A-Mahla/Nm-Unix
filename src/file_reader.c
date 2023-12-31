/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/29 21:33:41 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/13 19:23:18 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


static int	read_file(int fd, struct filedata_s *binary);
static bool	check_magic(struct filedata_s *binary);
static void	err_file(char *filename);


int	open_file(struct filedata_s **binary, char *filename)
{
	int	fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		goto err;
	if ((*binary = malloc(sizeof(struct filedata_s))) == NULL)
		goto err;
	(*binary)->file = NULL;
	(*binary)->symtab = NULL;
	(*binary)->strtab = NULL;
	(*binary)->name = filename;
	if (read_file(fd, *binary) == FAILURE)
		goto exit_failure;
	close(fd);
	return SUCCESS;
err:
	err_file(filename);
exit_failure:
	if (fd >= 0)
		close(fd);
	return FAILURE;
}


int	read_file(int fd, struct filedata_s *binary)
{
	int		rd;
	int		count;

	if (fstat(fd, &binary->statbuf) < 0)
		goto err;
	if (binary->statbuf.st_size == 0)
		goto exit_failure;
	if ((binary->file = malloc(binary->statbuf.st_size)) == NULL)
		goto err;
	if ((rd = read(fd, binary->file, 64)) < 0)
		goto err;
	binary->size = rd;
	if (!check_magic(binary))
		goto exit_failure;
	count = binary->statbuf.st_size > INT_MAX ? INT_MAX : binary->statbuf.st_size;
	while ((rd = read(fd, binary->file + 64, count - 64)) > 0)
		binary->size += rd;
	if (rd < 0)
		goto err;
	return SUCCESS;
err:
	err_file(binary->name);
exit_failure:
	return FAILURE;
}


bool	check_magic(struct filedata_s *binary)
{
	unsigned char	*e_indent;

	e_indent = (unsigned char *)binary->file;
	if (binary->size != 64)
		goto err;
	if (ft_memcmp(e_indent, ELF_MAGIC, ELF_MAGIC_SIZE) != 0)
		goto err;
	if (e_indent[EI_CLASS] != ELFCLASS32 && e_indent[EI_CLASS] != ELFCLASS64)
		goto err;
	binary->ei_class = e_indent[EI_CLASS];
	return true;
err:
	ft_dprintf(2, "nm: %s: file format not recognized\n", binary->name);
	return false;
}


void	err_file(char *filename)
{
	if (errno == EISDIR) {
		ft_dprintf(2, "nm: Warning: '%s' is a directory\n", filename);
	} else if (errno == ENOENT) {
		ft_dprintf(2, "nm: '%s': No such file\n", filename);
	} else {
		ft_dprintf(2, "nm: %s: ", filename);
		perror(NULL);
	}
}
