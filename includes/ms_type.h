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

#ifndef MS_TYPE_H
# define MS_TYPE_H

typedef enum e_token_type
{
	T_UNKNOWN,
	T_WORD,         // mot
	T_PIPE,         // |
	T_REDIR_IN,     // <
	T_REDIR_OUT,    // >
	T_REDIR_APPEND, // >>
	T_HEREDOC,      // <<
	T_EOF,          // gerent les VAR dans les heredocs
	T_EOF_Q,        //"EOF" ou 'EOF' -> ne pas gerer les expansions de variables dans les heredocs
	T_ARG           // Expansion de variable
}   t_token_type;

typedef	enum e_bool
{
	FALSE,
	TRUE	
}	t_bool;

#endif