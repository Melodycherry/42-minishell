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

void	create_av(t_shell *shell, t_token *current)
{
	int		i;
	char	**av;

	i = 0;
	av = malloc(sizeof(char *) * (shell->tlist.token_cnt + 1));
	if (!av)
		unfructuous_malloc(shell);
	while (i < shell->tlist.token_cnt)
	{
		if (current->type == T_ARG)
			av[i] = ft_strdup(current->var_value);
		else
			av[i] = ft_strdup(current->value);
		if (!av[i])
			free_mid_tab(shell, &av, i);
		current = current->next;
		i++;
	}
	av[i] = NULL;
	free_tab(&shell->executor.av);
	shell->executor.av = av;
}

t_bool	is_absolative(char *str)
{
	if (ft_strchr(str, '/'))
		return (TRUE);
	return (FALSE);
}
