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
# include "ms_type.h"
//# include "ms_utils.h"

# define PROMPT "Les codeuses du dimanche : "

#endif
