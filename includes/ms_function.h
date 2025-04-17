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

//fonctions tests a supprimer apres
void	print_tab(char **tab);

//fonctions qu on garde
void	bubble_tab(char **tab);
void	init_all(t_shell *shell);
void	init_list(t_shell *shell);
void	free_token_list(t_shell *shell);
void	free_mid_tab(char **strs, int i);
void	free_tab(t_shell *shell, char **tab);
void	insert_base_list(t_tlist *tlist, t_token *token);

char	**cpy_tab(char **tab);

int		main(int ac, char **av, char **env);

t_token	*create_token(int type, char *value);