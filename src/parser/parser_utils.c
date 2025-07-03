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

t_bool	ft_isoperator(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (TRUE);
	return (FALSE);
}

// void	handle_only_quotes(t_shell *shell, t_token *token)
// {
// 	int	i;

// 	i = 0;
// 	if (token == NULL || ft_strlen(token->value) == 0)
// 		return (FALSE);
// 	while (token->value[i])
// 	{
// 		if (token->value[i] != '"')
// 			return ;
// 		i++;
// 	}
// 	i = 0;
// 	while (token->value[i])
// 	{
// 		if (token->value[i] != '\'')
// 			return ;
// 		i++;
// 	}
// 	if (ft_strlen(token->value) % 2 == 0)
// 		return (error_message(shell, "command not found"));
// 	else
// 		return (error_message(shell, "Minishell does not handle that"));
// }

char	*error_multiple_operator(t_token *token, t_shell *shell)
{
	if (shell->tlist.token_cnt > 1)
	{
		while (token)
		{
			if (token->next)
			{
				if (token->type == 3 && token->next->type == 4)
					token = token->next;
				else if ((token->type >= 2 && token->type <= 6)
					&& (token->next->type >= 2 && token->next->type <= 6))
					return (token->value);
			}
			token = token->next;
		}
	}
	return (NULL);
}

void	extract_dbl_token(t_shell *shell, int *i, int *j, t_token *current)
{
	(*i) = (*i) + 2;
	create_insert_token(shell, *i, *j, current);
}

void	extract_sgl_token(t_shell *shell, int *i, int *j, t_token *current)
{
	(*i)++;
	create_insert_token(shell, *i, *j, current);
}
