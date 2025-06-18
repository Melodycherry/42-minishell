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

// #include "minishell.h"

// void handle_heredoc(t_shell *shell)
// {
//  	(void)shell;
// }

// int	nb_heredoc(t_shell *shell, t_token *token)
// {
// 	shell->executor.nb_heredoc = 0;
// 	while (token->next)
// 	{
// 		if (token->type == T_HEREDOC)
// 			shell->executor.nb_heredoc++;
// 		token = token->next;
// 	}
// }

// char **create_hd_eof(t_shell *shell, t_token *token)
// {
// 	char **tab;

// 	tab = malloc(sizeof (char *) * shell->executor.nb_heredoc + 1);

// }

// si on a un (<< + rien) = erreur
// si on a un (<< EOF << rien) = execution du heredoc 1x + erreur apres
// si on a un (<< EOF << EOF << EOF) -> aura besoin de 3 EOF

// si on un "EOF" -> expansion pas faite
// si on a un 'EOF' -> expansion pas faite

// si on un "E'OF -> ne sort jamais