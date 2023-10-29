/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   nm.c                                            :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/29 21:07:46 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/30 00:32:01 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

# include "nm.h"


void	nm(char *filename)
{
	struct filedata_s	*binary = NULL;

	if (open_file(&binary, filename) == FAILURE)
		goto exit_failure;
	goto exit_success;
exit_failure:
	exit_free(binary);
	exit(1);
exit_success:
	exit_free(binary);
}


int	main(int ac, char **av)
{
	if (ac < 2) {
		nm("a.out");
	}
	for (int i = 1; i < ac; i++)
		nm(av[i]);
	return 0;
}
