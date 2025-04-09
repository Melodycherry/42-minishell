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

// structure qui gere toutes les autres structures
typedef struct s_shell
{
	t_cmd		*cmd;
	t_lexer		*lexer;
	t_parser	*parser;
	t_expander	*expander;
	t_executor	*executor;
}	t_shell;

// tout ce qu on recoit dans le main
typedef struct s_cmd
{
	int		ac;
	char	*prompt;
	char	*path; //si utile
	char	**av;
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

#endif
