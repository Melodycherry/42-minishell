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

// tout ce qu on recoit dans le main
// j ai enlevé les ac, av qui seront inutiles, ma dit Nico. 
typedef struct s_cmd
{
	char	*prompt;
	char	*path; //si utile -> ce sera utile dans ce qu on reçoit de readline 
	char	**envp;
	char	**envp_copy;
}	t_cmd;

typedef struct s_lexer
{

}	t_lexer;

typedef struct s_parser
{

}	t_parser;

typedef struct s_expander
{

}	t_expander;

typedef struct s_executor
{

}	t_executor;

typedef enum e_token_type
{
    T_WORD,
    T_PIPE,
    T_REDIR_IN,     // <
    T_REDIR_OUT,    // >
    T_REDIR_APPEND, // >>
    T_HEREDOC,      // <<
    T_EOF
}   t_token_type;

typedef struct s_token
{
	t_token_type	type; // Modif pour utiliser enumeration above 
	char			*value;
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
	t_tlist		*tlist;
	t_cmd		*cmd;
	t_lexer		*lexer;
	t_parser	*parser;
	t_expander	*expander;
	t_executor	*executor;
}	t_shell;

#endif
