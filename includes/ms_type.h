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
	FALSE,			//faux
	TRUE			//vrai
}	t_bool;

typedef	enum e_envp
{
	NON_EXISTANT, 	//la variable n existe pas
	TO_EXPORT, 		//a mettre que dans le tableau env_export
	TO_ENV,
	TO_BOTH			//il y a un = donc a mettre dans les 2
}	t_envp;

#endif