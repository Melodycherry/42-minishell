/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*      LES CODEUSES DU DIMANCHE                                             */
/*      FONT UN MINISHELL                                                    */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "minishell.h"

void	find_range(t_shell *shell)
{
	int	i;

	i = shell->executor.end;
	if (i != 0 || shell->executor.start != 0)
		i++;
	shell->executor.start = i;
	while (shell->executor.av[i])
	{
		if (ft_strcmp(shell->executor.av[i], "|") == 0)
			break ;
		i++;
	}
	shell->executor.end = i - 1;
}

char	**split_args(t_shell *shell, char **av)
{
	char	**dest;
	int		i;
	int		start;
	int		end;

	find_range(shell);
	i = 0;
	start = shell->executor.start;
	end = shell->executor.end;
	dest = malloc(sizeof(char *) * (end - start + 2));
	if (!dest)
		return (NULL); // TODO: sorite malloc pourri
	while (start <= end && av[start])
	{
		dest[i] = ft_strdup(av[start]);
		if (!dest[i])
			free_mid_tab(&dest, i);
		i++;
		start++;
	}
	dest[i] = NULL;
	return (dest);
}

void	nb_pipe(t_shell *shell, t_token *token)
{
	shell->executor.nb_pipe = 0;
	while (token->next)
	{
		if (token->type == T_PIPE)
			shell->executor.nb_pipe++;
		token = token->next;
	}
}
