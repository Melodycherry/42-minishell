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

// gestion des expansions
void	expansion(t_shell *shell)
{
	t_token	*token;

	token = shell->tlist.head;
	check_var_env(shell, shell->tlist.head);
	while (token)
	{
		if (token->type == T_ARG)
		{
			expand_var(shell, token);
			if (is_quote_string(token->value))
				delete_quotes_value(token);
		}
		if (token->type == T_WORD)
		{
			if (is_quote_string(token->value))
				delete_quotes_value(token);
		}
		token = token->next;
	}
}

void	expand_var(t_shell *shell, t_token *token)
{
	int		i;
	int		j;
	char	*value;

	value = token->value;
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '"')
			expand_double_quote(shell, token, &i, &j);
		else if (value [i] == '\'')
			expand_single_quote(token, &i, &j);
		else if (value[i] == '$')
			expand_dollar(shell, token, &i, &j);
		else
			i++;
	}
	if (i > j)
		token->var_value
			= join_free(token->var_value, &value[j], (i - j));
}

void	expand_single_quote(t_token *token, int *i, int *j)
{
	char	*value;

	value = token->value;
	if (*i > *j)
		token->var_value
			= join_free(token->var_value, &value[*j], (*i - *j));
	(*i)++;
	(*j) = (*i);
	while (value[*i] && value[*i] != '\'')
	{
		while (value[*i] && value[*i] != '\'')
			(*i)++;
		if (*i > *j)
		{
			token->var_value
				= join_free(token->var_value, &value[*j], (*i - *j));
			(*j) = (*i);
		}
	}
	(*i)++;
	*j = *i;
}

void	expand_double_quote(t_shell *shell, t_token *token, int *i, int *j)
{
	char	*value;

	value = token->value;
	if (*i > *j)
		token->var_value
			= join_free(token->var_value, &value[*j], (*i - *j));
	(*i)++;
	(*j) = (*i);
	while (value[*i] && value[*i] != '"')
	{
		while (value[*i] && value[*i] != '$' && value[*i] != '"')
			(*i)++;
		if (*i > *j)
		{
			token->var_value
				= join_free(token->var_value, &value[*j], (*i - *j));
			(*j) = (*i);
		}
		if (value[*i] == '$')
			expand_dollar(shell, token, i, j);
	}
	(*i)++;
	*j = *i;
}

void	expand_dollar(t_shell *shell, t_token *token, int *i, int *j)
{
	char	*value;
	char	*rec_var;

	value = token->value;
	if (*i > *j)
		token->var_value = join_free(token->var_value, &value[*j], (*i - *j));
	if (value[*i] == '\0')
		return ;
	(*i)++;
	*j = *i;
	while (value[*i] && value[*i] != '$' && !ft_isquote(value[*i])
			&& !ft_isspace(value[*i]))
		(*i)++;
	if (*i > *j && var_exist(shell->cmd.envp_copy, &value[*j], (*i - *j)))
	{
		rec_var = recup_var(shell->cmd.envp_copy, &value[*j], (*i - *j));
		token->var_value = join_free(token->var_value, rec_var,
				get_segment_len(rec_var));
		(*j) = (*i);
	}
	if (value[*i])
	{
		(*i)++;
		*j = *i;
	}
}
