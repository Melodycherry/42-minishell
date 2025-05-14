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
void 	expansion(t_shell *shell)
{
	t_token	*token;

	token = shell->tlist.head;
	check_var_env(shell, shell->tlist.head);
	while (token)
	{
		if (token->type == T_ARG)
			expand_var(shell, token);
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

// fonction qui va verifier et enregistrer au besoin la line dans la var_value
// ********* en cours ne pas juger merci ********
void	expand_var(t_shell *shell, t_token *token)
{
	int		i;
	int		j;
	int		size_new_v;
	char	*value;
	char	*rec_var;

	value = token->value;
	i = 0;
	while (value[i])
	{
		j = i;
		while (value[i] && value[i] != '$')
		{
			if (value[i] == '\'')
				find_next_quote('\'', value, &i);
			else
				i++;
		}
		if (value[i] == '$' || value[i] == '\0')
		{
			if (i > j)
				token->var_value = join_free(token->var_value, &value[j], (i - j));
			if	(value[i] == '\0')
				return;
			i++;
			j = i;
			while (value[i] != '$' && value[i] && !ft_isquote(value[i])
				&& !ft_isspace(value[i])) 
				i++;
			if (var_exist(shell->cmd.envp_copy, &value[j], (i - j)) == TRUE)
			{
				rec_var = recup_var(shell->cmd.envp_copy, &value[j], (i - j));
				size_new_v = ft_strlen_plusplus(rec_var);
				token->var_value = join_free(token->var_value, rec_var, size_new_v);
			}
		}
	}
}


//si c est un T_ARG
/* reboucler while dans les token, si c est un ARG on va modifier le VAR_VALUE avec les string expandues.
ex : hello$MELO -> hellohello
ex : $POUPOU -> cul
ex : $MELOpoupou -> $MELOpoupou
ex : $MELO$POUPOU -> hellocul
ex : $MELOhello$NICO$POUPOU -> hellohellocul
ex : "$MELOhello$NICO$POUPOU" -> hellohellocul
ex : '$MELOhello'$NICO$POUPOU -> $MELOhellocul

Pour faire ca il faudra passer sur chaque caractere, si le caractere est pas un $ on print enregistre chaque caractere. si c est un $->reveriier si il existe
si il existe on concatene au debut et sinon on skip et on passe a la suite*/



