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

int		main(int ac, char **av, char **env);

/*BUILTIN*/
void	print_export(char **tab);
void	handle_export(t_shell *shell);
void	put_in_env(t_shell *shell, char **old_env, char *new_value);
void	put_in_export(t_shell *shell, char **old_export, char *new_value);

t_bool  is_command(void);
t_bool	is_valid_var_name(t_token *token, t_shell *shell);

/*EXECUTOR*/

/*EXPANDER*/

/*LEXER*/
void	token_blank(t_shell *shell);
void	find_next_quote(char quote, char *line, int *i);

t_bool	ft_isquote(int c);
t_bool	is_next_quote(char quote, char *line, int i);

/*PARSER*/
t_bool	ft_isoperator(int c);
t_bool	is_token_error(t_token *token, t_shell *t_shell);

void	token_operator(t_shell *shell);
void	token_typedef(t_token *token);

/*SIGNALS*/
void	setup_signals(void);
void	signal_handler(int sig);

/*UTILS*/

/*BYEBYE*/
void    error_syntax_unset(char *line);
void    error_syntax_export(char *line);
void	free_token_list(t_shell *shell);
void	free_mid_tab(char **strs, int i);
void	free_tab(t_shell *shell, char **tab);

t_token	*free_mid_list(t_token *current);

/*CHAIN*/

/*INIT*/
int     ft_tablen(char **tab);

void	bubble_tab(char **tab);
void	init_all(t_shell *shell);
void	init_list(t_shell *shell);
void	cpy_envp(t_shell *shell, char **envp);
void	insert_base_list(t_tlist *tlist, t_token *token);
void	insert_mid_list(t_token *current, t_token *new_token, t_shell *shell);
void	create_insert_token(t_shell *shell, int i, int j, t_token *current);

char	**cpy_tab(char **tab);

t_token	*create_token(int type, char *value, int n);




//fonctions tests a supprimer apres
void	print_tab(char **tab);
void	print_token(t_token *token, int (*f)(const char *, ...));
void	print_token2(t_token *token, int (*f)(const char *, ...));
