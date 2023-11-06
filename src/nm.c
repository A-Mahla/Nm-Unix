/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   nm.c                                            :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/29 21:07:46 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/06 17:58:52 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "nm.h"


int		nm(int ac, char *filename);
void	exit_free(struct filedata_s	*binary);

// TO DELETE
void	testing(void);
//

int	main(int ac, char **av)
{
	int	ret = 0;

//	TO DELETE
//	testing();
//	return 0;
//

	if (ac < 2)
		nm(ret, "a.out");
	for (int i = 1; i < ac; i++) {
		if (nm(ac, av[i]) == FAILURE)
			ret++;
	}
	return ret;
}


int	nm(int ac, char *filename)
{
	struct filedata_s	*binary = NULL;

	if (open_file(&binary, filename) == FAILURE)
		goto exit_failure;
	if (parse_file(binary, ac) == FAILURE)
		goto exit_failure;
	if (ac > 2)
		ft_printf("\n%s:\n", binary->name);
	print_symbols(binary);
	exit_free(binary);
	return SUCCESS;
exit_failure:
	exit_free(binary);
	return FAILURE;
}


void	exit_free(struct filedata_s	*binary)
{
	if (binary && binary->file)
		free(binary->file);
	if (binary && binary->symtab)
		free(binary->symtab);
	if (binary)
		free(binary);
}
