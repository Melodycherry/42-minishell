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

void 	expansion(t_shell *shell, t_token *token)
{
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
		if(token->type == T_WORD)
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
char	*recup_var()
{
	// je sais qu il existe moult fonction quon a fait pour le export dans lesquel je peux piocher mais la je suis fatiguee
	return (NULL); // en attendant
}

// fonction qui va verifier et enregistrer au besoin la line dans la var_value
// ********* en cours ne pas juger merci ********
void	expand_var(t_shell *shell, t_token *token)
{
	int	i;
	int	j; //parametrer le debut de la section

	i = 0;
	while (token->value[i])
	{
		j = i;
		if (token->value[i] == '\'')
				find_next_quote('\'', token->value, &i);
		while (token->value[i] && token->value[i] != '$')
			i++;
		if (token->value[i] == '$')
		{
			if (i > j)
				token->var_value = join_free(token->var_value, &token->value[j], (i - j)); // si il y aavait qqc avant le $ on le concatene
			i++;
			j = i; // reset j apres le $
			while (token->value[i] != '$' && token->value[i] && !ft_isquote(token->value[i]) && !ft_isspace(token->value[i]))
							i++;
			if (var_exist(shell->cmd.envp_exp, &token->value[j], (i - j)) == TRUE) // si elle existe on cacatene ou byebye a la suite
				token->var_value = join_free(token->var_value, recup_var(), (i - j)); // cree une fonction RECUP_VAR qui retourne la string recupérée dans le tableau
		}
		i++;
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



