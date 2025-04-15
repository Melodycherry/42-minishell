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

#ifndef MINISHELL_H
# define MINISHELL_H

//verifier si tout est utiise

//readline
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
//le reste
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>

# include "ft_printf.h"
# include "libft.h"
# include "ms_struct_general.h"
# include "ms_struct_chain.h"
# include "ms_function.h"
//# include "ms_utils.h"

// free
void    free_token_list(t_shell *shell);
char	**free_mid_tab(char **strs, int i);
char	**free_tab(t_shell *shell, char **tab);

// Init
void	init_all(t_shell *shell);
void	init_list(t_shell *shell);
t_token	*create_token(int type, char *value);
void	insert_base_list(t_list *list, t_token *token);


# endif
