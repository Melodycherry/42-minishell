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

// verifie le type ARG et change T_WORD en T_ARG si la var existe -> env_export
// ************* seems GOOOOOOOOOOD **************
void	check_var_env(t_shell *shell, t_token *token)
{
	int	i;
	int	j;

	while (token)
	{
		i = 0;
		if (token->type == T_WORD)
		{
			while (token->value[i])
			{	
				if (token->value[i] == '\'')
					find_next_quote('\'', token->value, &i);
				else
				{
					while (token->value[i] != '$' && token->value[i])
						i++;
					if (token->value[i] == '$')
					{
						i++;
						j = i;
						while (token->value[i] != '$' && token->value[i]
							&& !ft_isquote(token->value[i])
							&& !ft_isspace(token->value[i]))
							i++;
						if (var_exist(shell->cmd.envp_copy,
								&token->value[j], (i - j)) == TRUE) // modif ici pour env et pas export 26.06
						{
							token->type = T_ARG;
							return ;
						}
						else
							i--;
					}
					if (token->value[i])
						i++;
				}
			}
		}
		token = token->next;
	}
}
