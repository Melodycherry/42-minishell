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

// void	handle_heredoc(t_shell *shell)
// {
//  	nb_heredoc(shell, shell->tlist.head);
// 	if (shell->executor.nb_heredoc > 0)
// 	{
// 		create_hd_eof(shell, shell->tlist.head);
// 	}
// }

// void	nb_heredoc(t_shell *shell, t_token *token)
// {
// 	shell->executor.nb_heredoc = 0;
// 	while (token->next)
// 	{
// 		if (token->type == T_HEREDOC)
// 			shell->executor.nb_heredoc++;
// 		token = token->next;
// 	}
// }

// /* pas fonctionnel*/
// char **create_heredoc(t_shell *shell)
// {
// 	int		i;
// 	char	*tmp;
// 	char	**tab;

// 	i = 0;
// 	tmp = readline("<");
// 	if (tmp)
// 	{
// 		tab[i] = tmp;
// 		i++;
// 	}
// 	free(tmp);
// 	return (tab);
// }

void	update_type_eof(t_token *token)
{
	int	i;

	i = 0;
	while (token->next)
	{
		if (token->type == T_HEREDOC)
		{
			if (token->next)
			{
				token->next->type = T_EOF;
				while (token->next->value[i])
				{
					if (ft_isquote(token->next->value[i]) == TRUE)
						token->next->type = T_EOF_Q;
					i++;
				}
			}
			else
				perror("pas de delimiteur faire gestion d erreur");
			i++;
		}
		token = token->next;
	}
}

/* fonction qui va supprimer les quotes dans la vlue -> qui est le EOF */
/**** en cours de creation ****/
void delete_quotes_eof(t_token *token)
{
	int	i;

	i = 0;
	while (token->next)
	{
		if (token->type == T_EOF_Q)
		{
			while (token->value[i])
			{
				;
			}
		}
		token = token->next;
	}
}



// si on a un (<< + rien) = erreur
// si on a un (<< EOF << rien) = execution du heredoc 1x + erreur apres
// si on a un (<< EOF << EOF << EOF) -> aura besoin de 3 EOF

// si on un "EOF" -> expansion pas faite
// si on a un 'EOF' -> expansion pas faite

// si on un "E'OF -> ne sort jamais
// EOF -> helloEOF n est pas un EOF

// si << EOF1 << EOF2 >> fichier -> que EOF2 rentre dans le fichier



// void	create_hd_eof(t_shell *shell, t_token *token)
// {
// 	int		i;
// 	char	**tab;

// 	i = 0;
// 	tab = malloc(sizeof (char *) * shell->executor.nb_heredoc + 1);
// 	if (!tab)
// 		return ;
// 	while (token->next)
// 	{
// 		if (token->type == T_HEREDOC)
// 		{
// 			if (token->next)
// 				tab[i] = token->next->value;
// 			else
// 				tab[i] = NULL;
// 			i++;
// 		}
// 		token = token->next;
// 	}
// 	tab[i] = NULL;
// 	shell->executor.hd_eof = tab;
// 	print_tab(shell->executor.hd_eof);
// }