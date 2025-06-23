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

#ifndef MS_STRUCT_H
# define MS_STRUCT_H

# include "ms_type.h"
// tout ce qu on recoit dans le main
// j ai enlevé les ac, av qui seront inutiles, ma dit Nico. 
typedef struct s_cmd
{
	//char	*path; //si utile -> ce sera utile dans ce qu on reçoit de readline 
	char	*line;
	char	**envp_copy;
	char	**envp_exp;
}	t_cmd;

typedef struct s_lexer
{
	int	single_quote;
	int double_quote;
	int	space;
}	t_lexer;

typedef struct s_builtin
{
	t_bool is_echo_n;
}	t_builtin;

typedef struct s_expander
{

}	t_expander;

typedef struct s_executor
{
	char 			**av;
	char 			**paths;
	char			**pipe_av;
	char			**redir_av;
	char			*redir_file;
	
	int				end;
	int				start;
	int				nb_pipe;
	int				nb_redir;
	int				nb_heredoc;
	int				nb_redir_wip;
	int				index_file_heredoc;

	t_bool			is_forked;
	t_token_type	redir_type;
}	t_executor;

typedef struct s_token
{
	t_token_type	type; // Modif pour utiliser enumeration above 
	char			*value;
	char			*var_value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_tlist
{
	int		token_cnt; // peut etre util, a voir
	t_token	*head;

}	t_tlist; 

// structure qui gere toutes les autres structures
typedef struct s_shell
{
	t_tlist		tlist;
	t_cmd		cmd;
	t_lexer		lexer;
	t_builtin	builtin;
	t_expander	expander;
	t_executor	executor;
}	t_shell;

#endif
