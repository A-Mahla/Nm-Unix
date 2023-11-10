/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/29 21:07:46 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/10 15:36:19 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


static int	nm(int ac, char *filename);
static void	exit_free(struct filedata_s	*binary);


int	main(int ac, char **av)
{
	int	ret = 0;

//	ft_printf("%d\n", ft_strcoll(
//				"mime/multipart.(*writerOnly.1).Write",
//				"mime/multipart.writerOnly.1.Write")
//	); // => -1
//	exit(0);

	if (ac < 2)
		nm(ret, "a.out");
	for (int i = 1; i < ac; i++) {
		if (nm(ac, av[i]) == FAILURE)
			ret++;
	}
	return ret;
}


static int	nm(int ac, char *filename)
{
	struct filedata_s	*binary = NULL;

	if (open_file(&binary, filename) == FAILURE)
		goto exit_failure;
	if (parse_file(binary, ac) == FAILURE)
			goto exit_failure;
	if (!binary->strtab)
		goto exit_success;
	if (ac > 2)
		ft_printf("\n%s:\n", binary->name);
	print_symbols(binary);
exit_success:
	exit_free(binary);
	return SUCCESS;
exit_failure:
	exit_free(binary);
	return FAILURE;
}


static void	exit_free(struct filedata_s	*binary)
{
	if (binary && binary->file)
		free(binary->file);
	if (binary && binary->symtab)
		free(binary->symtab);
	if (binary)
		free(binary);
}
