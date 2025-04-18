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
    T_WORD,
    T_PIPE,
    T_REDIR_IN,     // <
    T_REDIR_OUT,    // >
    T_REDIR_APPEND, // >>
    T_HEREDOC,      // <<
    T_EOF
}   t_token_type;

typedef	enum e_bool
{
	FALSE,
	TRUE	
}	t_bool;

#endif