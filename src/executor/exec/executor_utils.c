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

void	convert_list_to_av(t_shell *shell, t_token *current)
{
	int		i;
	char	**av;

	i = 0;
	av = malloc(sizeof(char *) * (shell->tlist.token_cnt + 1));
	if (!av)
		unfructuous_malloc(shell);
	while (i < shell->tlist.token_cnt)
	{
		if (current->type == T_VAR)
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
