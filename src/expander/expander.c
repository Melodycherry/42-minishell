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

// verifie le type ARG et change T_WORD en T_ARG si la var existe dans env_export
// ************* seems GOOOOOOOD **************
void	check_var_env(t_shell *shell, t_token *token)
{
	int	i;
	int	j;
	while (token)
	{
		i = 0;
		if(token->type == T_WORD)
		{
			while (token->value[i] != '$' && token->value[i])
				i++;
			if (token->value[i] == '$')
			{
				i++;
				j = i;
				while (token->value[i] != '$' && token->value[i] && !ft_isquote(token->value[i]))
					i++;
				if (var_exist(shell->cmd.envp_exp, &token->value[j], (i - j)) == TRUE)
				{
					token->type = T_ARG;
					return ;
				}
				i++;
			}
		}
		token = token->next;
	}
}

//si c est un T_ARG
/* reboucler while dans les token, si c est un ARG on va modifier le VAR_VALUE avec les string expandues.
ex : hello$MELO -> hellohello
ex : $POUPOU -> cul
ex : $MELOpoupou -> $MELOpoupou
ex : $MELO$POUPOU -> hellocul
ex : $MELOhello$NICO$POUPOU -> hellohellocul

Pour faire ca il faudra passer sur chaque caractere, si le caractere est pas un $ on print enregistre chaque caractere. si c est un $->reveriier si il existe
si il existe on concatene au debut et sinon on skip et on passe a la suite*/