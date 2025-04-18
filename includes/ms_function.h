/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*      LES CODEUSES DU DIMANCHE                                               */
/*      FONT UN MINISHELL                                                      */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#include "minishell.h"

void	init_all(t_shell *shell);
void	init_list(t_shell *shell);
void	free_token_list(t_shell *shell);
void	insert_base_list(t_tlist *tlist, t_token *token);

char	**cpy_tab(t_shell *shell);
void	free_mid_tab(char **strs, int i);
void	free_tab(t_shell *shell, char **tab);

void	signal_handler(int sig);
void	setup_signals(void);

int		main(int ac, char **av, char **env);

t_token	*create_token(int type, char *value);