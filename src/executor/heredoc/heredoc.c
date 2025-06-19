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

void	handle_heredoc(t_shell *shell)
{
 	nb_heredoc(shell, shell->tlist.head);
	if (shell->executor.nb_heredoc > 0)
	{
		create_hd_eof(shell, shell->tlist.head);
	}
}

void	nb_heredoc(t_shell *shell, t_token *token)
{
	shell->executor.nb_heredoc = 0;
	while (token->next)
	{
		if (token->type == T_HEREDOC)
			shell->executor.nb_heredoc++;
		token = token->next;
	}
}

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

/* pas fonctionnel*/
char **create_heredoc(t_shell *shell)
{
	int		i;
	char	*tmp;
	char	**tab;

	i = 0;
	tmp = readline("<");
	if (tmp)
	{
		tab[i] = tmp;
		i++;
	}
	free(tmp);
	return (tab);
}

/* j en sais rien */
void	extract_eof(t_shell *shell, t_token *token)
{
	int	i;
	while (token->next)
	{
		if (token->type == T_HEREDOC)
		{
			if (token->next)
				tab[i] = token->next->value;
			else
				tab[i] = NULL;
			i++;
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