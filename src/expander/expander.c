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

void	delete_quotes_value(t_token *token)
{
	int	i;
	int	j;
	char *new_line;

	i = 0;
	new_line = NULL;
	while (token->value[i])
	{
		j = i;
		while (token->value[i] && !ft_isquote(token->value[i]))
			i++;
		if	(token->value[i] == '\0')
			return (free(new_line));
		if (i > j)
			new_line = join_free(new_line, &token->value[j], (i - j));
		if (ft_isquote(token->value[i]) == TRUE)
		{
			j = i + 1;
			find_next_quote(token->value[i], token->value, &i);
			new_line = join_free(new_line, &token->value[j], (i - j - 1));
			i++;
		}
		else
			return ;
	}
	free(token->value);
	token->value = new_line;
}

// gestion des expansions
void 	expansion(t_shell *shell)
{
	t_token	*token;

	token = shell->tlist.head;
	check_var_env(shell, shell->tlist.head);
	while (token)
	{
		if (token->type == T_ARG)
		{
			expand_var(shell, token);
			delete_quotes_value(token);
		}
		if (token->type == T_WORD)
			delete_quotes_value(token);
		token = token->next;
	}
}

// verifie le type ARG et change T_WORD en T_ARG si la var existe dans env_export
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
						if (var_exist(shell->cmd.envp_exp, 
								&token->value[j], (i - j)) == TRUE)
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

//lidee est d avoir une fonctoin qui va chercher dans le tableau l endroit ou se trouve la var et retourner tout ce qui se passe apre le 1e =
char	*recup_var(char **envp, char *var_env, int len)
{
	int		i;
	int		j;
	int		k;
	char	*equal_sign;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		j = (int)(equal_sign - envp[i]);
		if (ft_strncmp(envp[i], var_env, j) == 0 && (envp[i][len] == '='))
		{
			j++;
			k = j;
			while (envp[i][j])
				j++;
			return (&envp[i][k]);
		}
		i++;
	}
	return (NULL);
}

int	ft_strlen_plusplus(char *str)
{
	int	i;

	i = 0;

	while(str[i] && str[i] != '$' && str[i] != '"')
		i++;
	return (i);
}

void expand_dollar(t_shell *shell, t_token *token, int *i, int *j)
{
	char *value;
	char *rec_var;
	
	value = token->value;
	if (*i > *j)
		token->var_value = join_free(token->var_value, &value[*j], (*i - *j));
	if	(value[*i] == '\0')
		return;
	(*i)++;
	*j = *i;
	while (value[*i] != '$' && value[*i] && !ft_isquote(value[*i])
			&& !ft_isspace(value[*i])) 
		(*i)++;
	if (var_exist(shell->cmd.envp_copy, &value[*j], (*i - *j)) == TRUE)
	{
		rec_var = recup_var(shell->cmd.envp_copy, &value[*j], (*i - *j));
		token->var_value = join_free(token->var_value, rec_var, ft_strlen_plusplus(rec_var));
		(*j) = (*i);
	}
}

void expand_double_quote(t_shell *shell, t_token *token, int *i, int *j)
{
	char *value;
	
	value = token->value;
	if (*i > *j)
		token->var_value = join_free(token->var_value, &value[*j], (*i - *j));
	(*i)++;
	(*j) = (*i);
	while (value[*i] != '"') 
	{
		while (value[*i] != '$' && value[*i] != '"') 
			(*i)++;
		if (*i > *j)
		{
			token->var_value = join_free(token->var_value, &value[*j], (*i - *j));
			(*j) = (*i);
		}
		if (value[*i] == '$')
			expand_dollar(shell, token, i, j);
	}
}

void expand_var(t_shell *shell, t_token *token)
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
		{
			find_next_quote(value[i], value, &i);
			j = i;
		}
		else if (value[i] == '$' || value[i] == '\0')
			expand_dollar(shell, token, &i, &j);
		i++;
	}
}
