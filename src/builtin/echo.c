/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*      LES CODEUSES DU DIMANCHE                                               */
/*      FONT UN MINISHELL                                                      */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#include "minishell.h"

/** 
 * echo – write arguments to the standard output
 * The echo utility writes any specified operands, separated by single blank (‘ ’) characters
    and followed by a newline (‘\n’) character, to the standard output.
    The following option is available:
    -n    Do not print the trailing newline character.
 */
void	builtin_echo(t_shell *shell)
{
	char **av;
	int i;

	// below modif pour redir 
	if (shell->executor.redir_av)
		av = shell->executor.redir_av;
	else
		av = shell->executor.av;
	i = 1;
	print_flag_n(shell, av, &i);
	if (shell->builtin.is_echo_n == TRUE)
	{
		while (av[i])
		{
			printf("%s", av[i]);
			if (av[i + 1])
				printf(" ");
			i++;
		}
	}
	else
	{
		while (av[i])
		{
			printf("%s", av[i]);
			if (av[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
}

void	print_flag_n(t_shell *shell, char **av, int *i)
{
	shell->builtin.is_echo_n = FALSE;
	*i = 1;
	while (av[(*i)])
	{
		if (is_flag_n(av[(*i)]) == TRUE)
			{
				shell->builtin.is_echo_n = TRUE;
				(*i)++;
			}
		else 
			break;
	}
}

t_bool is_flag_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (FALSE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
